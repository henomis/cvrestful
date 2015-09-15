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

static void reply(struct ns_connection *nc, const char *msg, size_t len) {
	struct ns_connection *c;
	char buf[5000];


	if(memcmp(msg,"hello",len) == 0) {
		snprintf(buf, sizeof(buf), "hello to you!");
	} else if(memcmp(msg,"GetEmployment",len) == 0) {
		snprintf(buf, sizeof(buf), "%s",json_employment);
	} else if(memcmp(msg,"GetPersonalProjects",len) == 0) {
		snprintf(buf, sizeof(buf), "%s",json_personal);
	} else if(memcmp(msg,"GetSkills",len) == 0) {
		snprintf(buf, sizeof(buf), "%s",json_skills);
	} else if(memcmp(msg,"GetMiscellaneous",len) == 0) {
		snprintf(buf, sizeof(buf), "%s",json_misc);
	} else {
		snprintf(buf, sizeof(buf), "What?!");
	}
	
	ns_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, buf, strlen(buf));

  //for (c = ns_next(nc->mgr, NULL); c != NULL; c = ns_next(nc->mgr, c)) {
  //  ns_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, buf, strlen(buf));
//  }
}

int parse_markdown(char *file, struct ns_connection *nc)
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

	if (in != stdin)
		fclose(in);

	/* performing markdown parsing */
	ob = bufnew(OUTPUT_UNIT);

	sdhtml_renderer(&callbacks, &options, 0);
	markdown = sd_markdown_new(0, 16, &callbacks, &options);

	sd_markdown_render(ob, ib->data, ib->size, markdown);
	sd_markdown_free(markdown);

	/* writing the result to stdout */
	//ret = fwrite(ob->data, 1, ob->size, stdout);
	ns_printf_http_chunk(nc, "%s", ob->data);

	/* cleanup */
	bufrelease(ib);
	bufrelease(ob);

	return 0;
}
static void handle_sum_call(struct ns_connection *nc,
			    struct http_message *hm)
{
	char n1[100], n2[100];
	double result;

	/* Get form variables */
	ns_get_http_var(&hm->body, "n1", n1, sizeof(n1));
	ns_get_http_var(&hm->body, "n2", n2, sizeof(n2));

	/* Send headers */
	ns_printf(nc, "%s",
		  "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

	/* Compute the result and send it back as a JSON object */
	result = strtod(n1, NULL) + strtod(n2, NULL);
	ns_printf_http_chunk(nc, "{ \"result\": %lf }", result);
	ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
}

static void ev_handler(struct ns_connection *nc, int ev, void *ev_data)
{
	struct http_message *hm = (struct http_message *) ev_data;
	struct websocket_message *wm =
	    (struct websocket_message *) ev_data;

	switch (ev) {
	case NS_HTTP_REQUEST:
		if (ns_vcmp(&hm->uri, "/api/v1/sum") == 0) {
			handle_sum_call(nc, hm);	/* Handle RESTful call */
		} else if (ns_vcmp(&hm->uri, "/api/info") == 0) {
			/* Send headers */
			ns_printf(nc, "%s",
				  "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
			ns_printf_http_chunk(nc, "%s", json_info);
			ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
		} else if (ns_vcmp(&hm->uri, "/api/person") == 0) {
			/* Send headers */
			ns_printf(nc, "%s",
				  "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
			ns_printf_http_chunk(nc, "%s", json_person);
			ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
		} else if (ns_vcmp(&hm->uri, "/api/profession") == 0) {
			/* Send headers */
			ns_printf(nc, "%s",
				  "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
			ns_printf_http_chunk(nc, "%s", json_profession);
			ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
		} else if (ns_vcmp(&hm->uri, "/api/education") == 0) {
			/* Send headers */
			ns_printf(nc, "%s",
				  "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
			ns_printf_http_chunk(nc, "%s", json_education);
			ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
		} else if (ns_vcmp(&hm->uri, "/api/mdeducation") == 0) {
			/* Send headers */
			ns_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
			parse_markdown("md/education.md",nc);
			//ns_printf_http_chunk(nc, "%s", json_education);
			ns_send_http_chunk(nc, "", 0);	/* Send empty chunk, the end of response */
		} else {
			ns_serve_http(nc, hm, s_http_server_opts);	/* Serve static content */
		}
      		//nc->flags |= NSF_SEND_AND_CLOSE;
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
