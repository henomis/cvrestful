/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "fossa.h"
#include "markdown.h"
#include "html.h"
#include "buffer.h"
#include "restful_server.h"

#define READ_UNIT 1024
#define OUTPUT_UNIT 64

static const char *s_http_port = "8000";
static struct ns_serve_http_opts s_http_server_opts;

static int is_websocket(const struct ns_connection *nc) {
  return nc->flags & NSF_IS_WEBSOCKET;
}


int send_markdown(char *file, struct ns_connection *nc, serving_type_t mode)
{
	struct buf *ib, *ob;
	int ret;
	FILE *in = fopen(file,"r");
	if(!in)
		return -1;

	struct sd_callbacks callbacks;
	struct html_renderopt options;
	struct sd_markdown *markdown;

	/* reading everything */
	ib = bufnew(READ_UNIT);
	bufgrow(ib, READ_UNIT);
	while ((ret = fread(ib->data + ib->size, 1, ib->asize - ib->size, in)) > 0) {
		ib->size += ret;
		bufgrow(ib, ib->size + READ_UNIT);
	}

	fclose(in);

	/* performing markdown parsing */
	ob = bufnew(OUTPUT_UNIT);

	sdhtml_renderer(&callbacks, &options, 0);
	markdown = sd_markdown_new(0, 16, &callbacks, &options);

	sd_markdown_render(ob, ib->data, ib->size, markdown);
	sd_markdown_free(markdown);

	/* writing the result to stdout */
	if(mode == MODE_REST) {
		printf("SEND GET %s\n",file);
		ns_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
		ns_printf_http_chunk(nc, "%s", ob->data);
		ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
	} else {
		printf("SEND WS %s\n",file);

		int to_alloc = ob->size + 1024;

		char *json = malloc(to_alloc);
		char *file2 = strdup(file);
		memset (json, '\0', to_alloc);
		strcat(json,"{\"");

		// md/misc.md
		char *ptr1 = strstr(file2,"/");
		if(!ptr1) {
			free(json);
			free(file2);
			return;
		}
		ptr1 += 1;

		char *ptr2 = strstr(file2,".");
		if(!ptr2) {
			free(json);
			free(file2);
			return;
		}
		*ptr2 = '\0';

		strcat(json,ptr1);
		strcat(json,"\": \"");

		ptr1 = ob->data;
		int count = 0;
		while(count < ob->size) {
			if(*ptr1 == '\n') {
				//strcat(json,"<br>");
			} else if(*ptr1 == '"') {
				strcat(json,"'");
			} else {
				memcpy(&json[strlen(json)],ptr1,1);
			}
			ptr1++;
			count++;
		}

		//memcpy(&json[strlen(json)],ob->data,ob->size);
		strcat(json,"\"}");
		printf("%s\n",json);

		ns_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, json, strlen(json));

		free(json);
		free(file2);
	}


	/* cleanup */
	bufrelease(ib);
	bufrelease(ob);

	return 0;
}


static void send_json(char *file, struct ns_connection *nc, serving_type_t mode)
{


#define READ_CHUNK (1024 * 1024)
	char buffer[READ_CHUNK];
	int ret = 0, sum = 0;
	char *ptr = buffer;


	if(strstr(file,"..") != NULL)
		return;

	FILE *fp = fopen(file,"r");
	if(!fp)
		return;


	if(mode == MODE_REST) {
		printf("GET /api/%s\n",file);
		ns_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	} else {
		printf("WS %s\n",file);
	}


	while((ret = fread(ptr,1,READ_CHUNK,fp)) != 0) {
		ptr+=ret;
		sum+=ret;
	}


	fclose(fp);


	if(mode == MODE_REST) {
		ns_send_http_chunk(nc,buffer,sum);
		ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
	} else {
		ns_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, buffer, sum);
	}

	return;

}


static void reply(struct ns_connection *nc, const char *msg, size_t len) {

	char *str = (char*)malloc(len+ 1);

	memset(str,'\0',len+1);
	memcpy(str,msg,len);

	if(strstr(str,"..") != NULL)
		return;

	if(strstr(str,"json/") != NULL) {
		str = realloc(str,len + 1 + strlen(".json"));
		strcat(str,".json");
		send_json(str, nc, MODE_WS);
	} else {

		str = realloc(str,len + 1 + strlen(".md"));
		strcat(str,".md");
		send_markdown(str, nc, MODE_WS);
	}
	
	free (str);

}

static void ev_handler(struct ns_connection *nc, int ev, void *ev_data)
{
	struct http_message *hm = (struct http_message *) ev_data;
	struct websocket_message *wm =
	    (struct websocket_message *) ev_data;
	char *ptr;

	switch (ev) {
	case NS_HTTP_REQUEST:

		if((ptr = strstr(hm->uri.p,"/api/json/")) != NULL) {

			char *ptr2 = strstr(ptr,"?");
			ptr += strlen("/api/");

			char *file = (char*) malloc(1024);
			memset(file,'\0',1024);

			memcpy(file,ptr,ptr2-ptr);
			strcat(file,".json");

			send_json(file, nc, MODE_REST);

			free(file);

		} else if((ptr = strstr(hm->uri.p,"/api/md/")) != NULL) {

			char *ptr2 = strstr(ptr,"?");
			ptr += strlen("/api/");

			char *file = (char*) malloc(1024);
			memset(file,'\0',1024);

			memcpy(file,ptr,ptr2-ptr);
			strcat(file,".md");

			send_markdown(file, nc, MODE_REST);
			free(file);

		} else {
			ns_serve_http(nc, hm, s_http_server_opts);	/* Serve static content */
		}

		break;
	case NS_WEBSOCKET_HANDSHAKE_DONE:
		/* New websocket connection. Tell everybody. */
		//broadcast(nc, "joined", 6);
		break;
	case NS_WEBSOCKET_FRAME:
		/* New websocket message. Tell everybody. */
		reply(nc, (char *) wm->data, wm->size);
		
		break;
	case NS_CLOSE:
		/* Disconnect. Tell everybody. */
		if (is_websocket(nc)) {
			reply(nc, "left", 4);
		}
		break;
	default:
		break;
	}
}



int main(int argc, char *argv[])
{
	struct ns_mgr mgr;
	struct ns_connection *nc;
	int i;


	/*printf("json_personal\n%s\n\n",json_personal);
	printf("json_skills\n%s\n\n",json_skills);
	printf("json_misc\n%s\n\n",json_misc);*/

	ns_mgr_init(&mgr, NULL);
	nc = ns_bind(&mgr, s_http_port, ev_handler);
	ns_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = ".";
	s_http_server_opts.enable_directory_listing = "yes";
	ns_set_protocol_http_websocket(nc);

	/* Process command line options to customize HTTP server */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-D") == 0 && i + 1 < argc) {
			mgr.hexdump_file = argv[++i];
		} else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
			s_http_server_opts.document_root = argv[++i];
		} else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
			s_http_server_opts.auth_domain = argv[++i];
		} else if (strcmp(argv[i], "-P") == 0 && i + 1 < argc) {
			s_http_server_opts.global_auth_file = argv[++i];
		} else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
			s_http_server_opts.per_directory_auth_file =
			    argv[++i];
		} else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
			s_http_server_opts.url_rewrites = argv[++i];
#ifndef NS_DISABLE_CGI
		} else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			s_http_server_opts.cgi_interpreter = argv[++i];
#endif
#ifdef NS_ENABLE_SSL
		} else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
			const char *ssl_cert = argv[++i];
			const char *err_str =
			    ns_set_ssl(nc, ssl_cert, NULL);
			if (err_str != NULL) {
				fprintf(stderr,
					"Error loading SSL cert: %s\n",
					err_str);
				exit(1);
			}
#endif
		}
	}

	printf("Starting RESTful server on port %s\n", s_http_port);
	for (;;) {
		ns_mgr_poll(&mgr, 1000);
	}
	ns_mgr_free(&mgr);

	return 0;
}
