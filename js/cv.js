
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
		url: "/api/info",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/info",0);

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
		notify("GET /api/info",1);
	});
	
}

function do_person()
{

	$.ajax({
		url: "/api/person",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/person",0);

		$("#t-person").hide();

		$("#person").html("");
		$("#person").append("<h2>Person:</h2>");
		$("#person").append("<ul><li><strong>Born</strong>: " + obj.person.born + "</li>" +
		"<li><strong>Nationality</strong>: " + obj.person.nationality + "</li>" +
		"<li><strong>Martial status</strong>: " + obj.person.mstatus + "</li></ul>");
		$("#person").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	})
	.fail(function() {
		notify("GET /api/person",1);
	});
	
}

function do_profession()
{

	$.ajax({
		url: "/api/profession",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/profession",0);

		$("#t-profession").hide();

		$("#profession").html("");
		$("#profession").append("<h2>Profession:</h2>");
		$("#profession").append("<ul><li><strong>Now</strong>: " + obj.profession.now + "</li></ul>");
		$("#profession").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
	})
	.fail(function() {
		notify("GET /api/profession",1);
	});
	
}

function do_education_old()
{

	$.ajax({
		url: "/api/education",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /api/education",0);

		$("#t-education").hide();
		$("#education").html("");

		$("#education").append("<h2>Education:</h2>");
	
		var text = "<ul>";	
		for(var k in obj.education) {
			text += "<li><strong>" + obj.education[k].date + "</strong>: " + obj.education[k].title + "</li>";
		}
		text += "</ul>";

		$("#education").append(text);
		$("#education").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
		
		$("#employment").show();
	})
	.fail(function() {
		notify("GET /api/education",1);
	});
	
}

function do_education()
{

	$.ajax({
		url: "/api/mdeducation",
		cache: false
		//dataType: "text"
	}).done(function(obj) {

		notify("GET /api/mdeducation",0);

		$("#t-education").hide();

		$("#education").html(obj);
		$("#education").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );
		$("#employment").show();
	})
	.fail(function() {
		notify("GET /api/education",1);
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
	var text = "";

	text += "<h2>Personal Projects:</h2>";
	text+="<ul>";
	for(var k in o) {

		text+="<li><strong>" + o[k].title + "</strong></li>";
		text+="<ul>";
		for (var j in o[k].projects) {
			text+="<li>" + o[k].projects[j] + "</li>";
		}
		text+="</ul>";

	}
	text+="</ul>";

	$("#d-personal").html(text);
	$("#d-personal").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

	$("#t-personal").hide();
	
}

function do_skills(o)
{
	var text = "";

	text += "<h2>Skills:</h2>";
	text+="<ul>";
	for(var k in o) {

		text+="<li><strong>" + o[k].title + "</strong></li>";
		text+="<ul>";
		for (var j in o[k].feat) {
			text+="<li>" + o[k].feat[j] + "</li>";
		}
		text+="</ul>";

	}
	text+="</ul>";

	$("#d-skills").html(text);
	$("#d-skills").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

	$("#t-skills").hide();
	
}

function do_misc(o)
{
	var text = "";

	text += "<h2>Languages:</h2>";
	text+="<ul>";
	var a = o.misc.languages;
	for(var k in a) {

		text+="<li><strong>" + a[k].title + "</strong>: " + a[k].value + "</li>";
		text+="<ul>";
		text+="</ul>";

	}
	text+="</ul>";
	text+="<h2>Interest:</h2>" + o.interest;

	$("#d-misc").html(text);
	$("#d-misc").animate({ backgroundColor: "#DFF0D8" }, 1000 ).animate({ backgroundColor: "#ffffff" }, 1000 );

	$("#t-misc").hide();
	
}

function do_ws() {
	notify("Connecting to ws://" + location.host + "/ws...",2);

	ws = new WebSocket('ws://' + location.host + '/ws');


	ws.onopen = function(ev)  { notify("Connecting to ws://" + location.host + "/ws",0); ws.send("GetEmployment");};
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
		} else if(typeof(obj.personal) === 'object') {
			do_personal(obj.personal);
		} else if(typeof(obj.skills) === 'object') {
			do_skills(obj.skills);
		} else if(typeof(obj.misc) === 'object') {
			do_misc(obj);
		} else {
			alert("obj?");
		}

	};
}



function do_howthis()
{
	$.ajax({
		url: "/json/howthis.json",
		cache: false,
		dataType: "json"
	}).done(function(obj) {

		notify("GET /json/howthis.json",0);
		$("#howthis-content").html(obj.text);
		$("#howthis-info").show();
	})
	.fail(function() {
		notify("GET /json/howthis.json",1);
	});
	
}


// callbacks
$( document ).ready(function() {
	$("#start").click(function() {do_start()});
	$("#btn-person").click(function() {do_person()});
	$("#btn-profession").click(function() {do_profession()});
	$("#btn-education").click(function() {do_education()});
	$("#btn-connect").click(function() {do_ws()});
	$("#btn-personal").click(function() { ws.send("GetPersonalProjects")});
	$("#btn-skills").click(function() { ws.send("GetSkills")});
	$("#btn-misc").click(function() { ws.send("GetMisc")});
	$("#howthis").click(function() { do_howthis()});
	$("#howthis-close").click(function() { $("#howthis-info").hide()});
});
