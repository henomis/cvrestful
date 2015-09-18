
// Create Base64 Object
var Base64={_keyStr:"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",encode:function(e){var t="";var n,r,i,s,o,u,a;var f=0;e=Base64._utf8_encode(e);while(f<e.length){n=e.charCodeAt(f++);r=e.charCodeAt(f++);i=e.charCodeAt(f++);s=n>>2;o=(n&3)<<4|r>>4;u=(r&15)<<2|i>>6;a=i&63;if(isNaN(r)){u=a=64}else if(isNaN(i)){a=64}t=t+this._keyStr.charAt(s)+this._keyStr.charAt(o)+this._keyStr.charAt(u)+this._keyStr.charAt(a)}return t},decode:function(e){var t="";var n,r,i;var s,o,u,a;var f=0;e=e.replace(/[^A-Za-z0-9\+\/\=]/g,"");while(f<e.length){s=this._keyStr.indexOf(e.charAt(f++));o=this._keyStr.indexOf(e.charAt(f++));u=this._keyStr.indexOf(e.charAt(f++));a=this._keyStr.indexOf(e.charAt(f++));n=s<<2|o>>4;r=(o&15)<<4|u>>2;i=(u&3)<<6|a;t=t+String.fromCharCode(n);if(u!=64){t=t+String.fromCharCode(r)}if(a!=64){t=t+String.fromCharCode(i)}}t=Base64._utf8_decode(t);return t},_utf8_encode:function(e){e=e.replace(/\r\n/g,"\n");var t="";for(var n=0;n<e.length;n++){var r=e.charCodeAt(n);if(r<128){t+=String.fromCharCode(r)}else if(r>127&&r<2048){t+=String.fromCharCode(r>>6|192);t+=String.fromCharCode(r&63|128)}else{t+=String.fromCharCode(r>>12|224);t+=String.fromCharCode(r>>6&63|128);t+=String.fromCharCode(r&63|128)}}return t},_utf8_decode:function(e){var t="";var n=0;var r=c1=c2=0;while(n<e.length){r=e.charCodeAt(n);if(r<128){t+=String.fromCharCode(r);n++}else if(r>191&&r<224){c2=e.charCodeAt(n+1);t+=String.fromCharCode((r&31)<<6|c2&63);n+=2}else{c2=e.charCodeAt(n+1);c3=e.charCodeAt(n+2);t+=String.fromCharCode((r&15)<<12|(c2&63)<<6|c3&63);n+=3}}return t}}

var ws;

function highlight(obj) {
	obj.animate("backgroud-color: 'green'");
	setTimeout(function(){  obj.animate("background-color: 'white'"); }, 2000);
}

function notify(value, w) {
	//clear classes
	$("#notify").removeAttr("class");
//Class(function() {return $( this ).prev().attr( "class" );});

	if(w == 0) {
		$("#notify").addClass("alert alert-success").html(value+" - Success!").fadeIn();
	} else if(w == 1) {
		$("#notify").addClass("alert alert-danger").html(value+" - Error!").fadeIn();
	} else if(w == 2) {
		$("#notify").addClass("alert alert-warning").html(value).fadeIn();
	}
	setTimeout(function(){  $("#notify").fadeOut(); }, 2000);
}

function do_start()
{

	$.ajax({
		url: "/api/json/info",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/json/info",0);

		$("#start").hide();

		$(".lead").html("");
		$(".lead").append("<strong>Tel</strong>: " + obj.info.tel + "<br>");
		$(".lead").append("<strong>E-mail</strong>: <a target='_blank' href='mailto:" + obj.info.email + "'>" + obj.info.email + "</a><br>");
		$(".lead").append("<strong>Blog</strong>: <a target='_blank' href='" + obj.info.blog + "'>" + obj.info.blog + "</a>");
		$(".lead").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
		$(".api-table").show();	
		$("#howthis").show();
		$("#howthis").addClass('howthis');
	})
	.fail(function() {
		notify("GET /api/json/info",1);
	});
	
}

function do_person()
{

	$.ajax({
		url: "/api/json/person",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/json/person",0);

		$("#t-person").hide();

		$("#person").html("");
		$("#person").append("<h2>Person:</h2>");
		$("#person").append("<ul><li><strong>Born</strong>: " + obj.person.born + "</li>" +
		"<li><strong>Nationality</strong>: " + obj.person.nationality + "</li>" +
		"<li><strong>Martial status</strong>: " + obj.person.mstatus + "</li></ul>");
		$("#person").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	})
	.fail(function() {
		notify("GET /api/json/person",1);
	});
	
}

function do_profession()
{

	$.ajax({
		url: "/api/json/profession",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/json/profession",0);

		$("#t-profession").hide();

		$("#profession").html("");
		$("#profession").append("<h2>Profession:</h2>");
		$("#profession").append("<ul><li><strong>Now</strong>: " + obj.profession.now + "</li></ul>");
		$("#profession").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	})
	.fail(function() {
		notify("GET /api/json/profession",1);
	});
	
}


function do_education()
{

	$.ajax({
		url: "/api/md/education",
		cache: false
		//dataType: "text"
	}).done(function(obj) {

		notify("GET /api/md/education",0);

		$("#t-education").hide();

		$("#education").html(obj);
		$("#education").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
		$("#employment").show();
	})
	.fail(function() {
		notify("GET /api/md/education",1);
	});
	
}

function do_employment(o)
{
	var text = "";

	text += "<h2>Employment:</h2>";
	for(var k in o) {

		text+="<h3>" + o[k].date + ": " + o[k].title + "</h3>";
		text+="<ul>";
		for (var j in o[k].projects) {
			text+="<li>" + o[k].projects[j].title + "</li><ul>";
			for (var l in o[k].projects[j].activities) {
				text+="<li>" + o[k].projects[j].activities[l] + "</li>";
			}
			text+="</ul>";
		}
		text+="</ul>";

	}

	$("#employment").css("text-align","left");
	$("#employment").html(text);
	$("#employment").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

	$(".websocket-table").show();
	
}

function do_personal(o)
{

	$("#d-personal").html(Base64.decode(o));
	$("#d-personal").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	notify("GET ws:/api/md/personal",0);
	$("#t-personal").hide();
	
}

function do_skills(o)
{

	$("#d-skills").html(Base64.decode(o));
	$("#d-skills").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	notify("GET ws:/api/md/skills",0);
	$("#t-skills").hide();
	
}

function do_misc(o)
{

	$("#d-misc").html(Base64.decode(o));
	$("#d-misc").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	notify("GET ws:/api/md/misc",0);

	$("#t-misc").hide();
	
}

function do_ws() {
	notify("Connecting to ws://" + location.host + "/ws...",2);

	ws = new WebSocket('ws://' + location.host + '/ws');


	ws.onopen = function(ev)  { notify("Connecting to ws://" + location.host + "/ws",0); ws.send("json/employment");};
	ws.onerror = function(ev) { notify("Connecting to ws://" + location.host + "/ws",1); };
	ws.onclose = function(ev) {  };
	ws.onmessage = function(ev) {

		var obj;
		try {
			obj = jQuery.parseJSON(ev.data);
		} catch(e) {
			return;
		}

		if(typeof(obj.employment) === 'object') {
			do_employment(obj.employment);
		} else if(obj.projects) {
			do_personal(obj.projects);
		} else if(obj.skills) {
			do_skills(obj.skills);
		} else if(obj.misc) {
			do_misc(obj.misc);
		} else {
			alert("obj?");
		}

	};
}



function do_howthis()
{
	$.ajax({
		url: "/api/json/howthis",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/json/howthis",0);
		$("#howthis-content").html(obj.text);
		$("#howthis-info").show();
	})
	.fail(function() {
		notify("GET /api/json/howthis",1);
	});
	
}


// callbacks
$( document ).ready(function() {
	$("#start").click(function() {do_start()});
	$("#btn-person").click(function() {do_person()});
	$("#btn-profession").click(function() {do_profession()});
	$("#btn-education").click(function() {do_education()});
	$("#btn-connect").click(function() {do_ws()});
	$("#btn-personal").click(function() { ws.send("md/projects")});
	$("#btn-skills").click(function() { ws.send("md/skills")});
	$("#btn-misc").click(function() { ws.send("md/misc")});
	$("#howthis").click(function() { do_howthis()});
	$("#howthis-close").click(function() { $("#howthis-info").hide()});
});
