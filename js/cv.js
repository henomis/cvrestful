
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

	$("#d-personal").html(o);
	$("#d-personal").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

	$("#t-personal").hide();
	
}

function do_skills(o)
{

	$("#d-skills").html(o);
	$("#d-skills").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

	$("#t-skills").hide();
	
}

function do_misc(o)
{

	$("#d-misc").html(o);
	$("#d-misc").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

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
