#ifndef _RESTFUL_H_
#define _RESTFUL_H_


static const char *json_info = "{ \"info\" : { \"tel\": \"+39.339.1298166\", \"email\": \"henomis@gmail.com\", \"blog\": \"http://henomis.wordpress.com\" } }";
static const char *json_person = "{ \"person\": {\"born\": \"November 7<sup>th</sup> 1979\", \"nationality\": \"Italian\", \"mstatus\": \"Married\"} }";
static const char *json_profession = "{ \"profession\": {\"now\": \"GNU/Linux embedded system developer at <a href='http://www.inim.biz'>Inim Electronics</a>\"} }";
static const char *json_education = "{\"education\": [{ \"date\":\"March 2014\", \"title\": \"Cloud Computing Concepts - University of Illinois at Urbana-Champaign (<a href='https://www.coursera.org/account/accomplishments/certificate/3TJ4EN23LX'>Certificate</a>) - Coursera.org\"},{ \"date\":\"Decembert 2014\", \"title\": \"Introduction to Electronics - Georgia Institute of Technology (<a href='https://www.coursera.org/account/accomplishments/certificate/3S93NKQBQ9'>Certificate</a>) - Coursera.org\"},{ \"date\":\"November 2014\", \"title\": \"Linear Circuits - Georgia Institute of Technology (<a href='https://www.coursera.org/account/accomplishments/certificate/H7GHHAQNH7'>Certificate</a>) - Coursera.org\"},{\"date\": \"March 2005\", \"title\": \"Master Degree in computer science at the Department of Computer Science, University of Bologna, Italy.\"}, {\"date\": \"1998\", \"title\": \"Diploma at “Liceo Statale B. Rossetti” in San Benedetto del Tronto, Italy.\"}]}";


static const char *json_employment = "{ \"employment\": [ \
{ \"date\": \"2006-now\", \"title\": \"GNU/Linux embedded system developer at <a href='http://www.inim.biz'>Inim Electronics</a>.\", \
\"projects\": [ \
	{ \"title\": \"<strong>Project <a href='http://www.inim.biz/prodotto.php?node=355&lang=en'>Evolution</a></strong>: <span class='cv-info'>home automation</span> keypad for SmartLiving intrusion detection system.\", \"activities\": [\"Research and selection of the hardware platform\", \"Custom SDK development and <span class='cv-info'>GNU/Linux</span> Filesystem creation (based on <a href='buildroot.uclibc.org'>Buildroot</a>)\", \"Keypad <span class='cv-info'>GUI</span> design and development using <a href='http://www.qt.io'>Qt</a>/C++\", \"Custom protocols development over <span class='cv-info'>RS232</span> and <span class='cv-info'>TCP/IP</span> using C, sockets and various tools and libs\", \"Software tools creation for the testing team using BASH, sed, awk, zenity, and other Unix tools\", \"<span class='cv-info'>Documentation</span> guidelines drafting for the documentation team.\"]}, \
	{ \"title\": \"<strong>Project <a href='http://www.inim.biz/prodotto.php?node=81&lang=en'>SmartLAN/G</a></strong>: ethernet expansion board for SmartLiving intrusion detection system.\", \"activities\": [\"Research and selection of the hardware platform\", \"Custom SDK development and <span class='cv-info'>GNU/Linux</span> Filesystem creation (based on <a href='buildroot.uclibc.org'>Buildroot</a>)\", \"Custom protocols development over <span class='cv-info'>RS232</span> and <span class='cv-info'>TCP/IP</span> using C sockets and various tools and libs\",\"Development of a <span class='cv-info'>RESTFUL API</span> server and an <span class='cv-info'>HTML5</span> responsive Web interface\", \"Events queue and email delivery system development\", \"<span class='cv-info'>ModBus/IP</span> and <span class='cv-info'>SIA-IP</span> protocols server development\", \"<span class='cv-info'>ONVIF</span> protocol integration\", \"Software tools creation for the testing team using BASH, sed, awk, zenity, and other Unix tools\", \"Documentation guidelines drafting for the documentation team.\"]}, \
	{ \"title\": \"<strong>Project <a href='http://www.inim.biz/prodotto.php?node=135&lang=en'>SmartLAN</a></strong>: ethernet expansion board for SmartLoop fire detection system.\", \"activities\": [\"Research and selection of the hardware platform\", \"Custom SDK development and <span class='cv-info'>GNU/Linux</span> Filesystem creation (based on <a href='buildroot.uclibc.org'>Buildroot</a>)\", \"Custom protocols development over <span class='cv-info'>RS232</span> and <span class='cv-info'>TCP/IP</span> using C sockets and various tools and libs\",\"Development of a <span class='cv-info'>RESTFUL API</span> server and a web interface\", \"Events queue and email delivery system development\", \"Software tools creation for the testing team using BASH, sed, awk, zenity, and other Unix tools\", \"Documentation guidelines drafting for the documentation team.\"]}, \
	{ \"title\": \"<strong>Project <a href='http://www.inim.biz/prodotto.php?node=105&lang=en'>Hornet</a></strong>: token-ring full stack for SmartLoop fire detection system.\", \"activities\": [\"Design and development of a custom <span class='cv-info'>token-ring</span> stack\",\"<span class='cv-info'>Firmware</span> development on Renesas H8SX microcontroller\" ]} \
]}, \
{ \"date\": \"2008-2011 (as second job)\", \"title\": \"Freelance IT consultant.\", \
\"projects\": [ \
	{ \"title\": \"<strong>Software development</strong>\", \"activities\": [\"Development of various <span class='cv-info'>WxWdgets</span> components\", \"GNU/Linux <span class='cv-info'>kernel drivers</span> customization\", \"Web site development\"]}, \
	{ \"title\": \"<strong>Teaching</strong>\", \"activities\": [\"Various GNU/Linux based courses (O.S. installation, office automation, graphics, audio, etc.)\"]}, \
	{ \"title\": \"<strong>Sysadmin</strong>\", \"activities\": [\"GNU/Linux based firewalls installation and configuration.\"]} \
]}, \
{ \"date\": \"2005\", \"title\": \"Software developer at Bentel Security.\", \
\"projects\": [ \
	{ \"title\": \"<strong>Software development</strong>\", \"activities\": [\"Internal usage software development.\", \"Development of WIN32 DLL for the cryptographic layer of SIA-IP protocol\", \"Reserch and selection of a GNU/Linux based embedded system.\"]} \
]}, \
{ \"date\": \"2004\", \"title\": \"System administrator at Università Bologna IT department.\", \
\"projects\": [ \
	{ \"title\": \"<strong>Sysadmin</strong>\", \"activities\": [\"Installation, configuration and administration of an <span class='cv-info'>OpenBSD</span> host of students.cs.unibo.it public network.\"]} \
]} \
]}";


static const char *json_personal = "{ \
    \"personal\": [ \
        { \
            \"title\": \"Hosted at SourceForce (<a href='http://sourceforge.net/users/simone_vellei'>repository</a>)\", \
            \"projects\": [ \
                \"<a href='http://www.flatnuke.org'>FlatNuke</a> - Content Management System based on flat-file database\", \
                \"<a href='http://stork.sf.net'>Stork</a> -  SystemV Transport tO Remote Kernel, Distributed SystemV layer extension for Linux kernel, 2.6 (Master degree thesis).\", \
                \"<a href='http://sourceforge.net/projects/freepops/'>FreePOPs</a> - Extensible POP3 server (Italian OpenSourceContest 2004 winner).\", \
               \"<a href='http://eucaristos.sf.net'>EucaristOS</a> A small GNU/Linux distribution with openMosix clusters support\" \
            ] \
        }, \
        { \
            \"title\": \"Hosted at GitLab (<a href='https://gitlab.com/henomis'>repository</a>)\", \
            \"projects\": [ \
                \"<a href='https://gitlab.com/virtualdamien/virtualdamien/tree/master'>VirtualDamien</a>. Dynamic generator of Damien Hirst spot painting art.\", \
                \"<a href='https://gitlab.com/virtualjerry/virtualjerry/tree/master'>VirtualJerry</a>. Dynamic generator of Jerry Bergonzi jazz method exercises\", \
                \"<a href='https://gitlab.com/emoneyc/btcec/tree/master'>BtceC</a> and <a href='https://gitlab.com/emoneyc/vircurexc/tree/master'>VircurexC</a>. Btc-e.com and Vircurex.com digital currency trading API clients in C.\" \
            ] \
        },{ \
           \"title\": \"Conferences\", \
            \"projects\": [ \
               \"Conferences speaker in italian language (<a href='https://henomis.wordpress.com/conferenze/'>complete list</a>).\" \
            ] \
        } \
]}";

static const char *json_skills =  "{ \
    \"skills\": [ \
        { \
            \"title\": \"Operating systems\", \
            \"feat\": [ \
                \"Unix: GNU/Linux, FreeBSD, OpenBSD, NetBSD.\", \
                \"MS Windows: Windows 95/98/2000/XP/NT, MS-DOS.\" \
            ] \
        }, \
        { \
            \"title\": \"Developing\", \
            \"feat\": [ \
                \"Programming: C, C++, Java, J2ME, Pascal, GTK+, WxWidgets, SDL, QT.\", \
                \"Script: Perl, LUA, bash, awk, sed\", \
                \"Web: HTML, PHP, JavaScript, XML, XSLT, RSS, RDF, CSS, Ajax, jQuery\" \
            ] \
        }, \
        { \
            \"title\": \"Networking\", \
            \"feat\": [ \
                \"Ability to build computer networks and to provide services.\", \
                \"Good experience with the following protocols: ftp, http, smtp, pop3, imap, irc, smb, dhcp, ssl, ssh.\", \
                \"Experience with network security and cryptographic tools.\", \
                \"Experience in virtualization techniques (Qemu, UML, PearPC, VirtualBox)\", \
                \"Experience in high performace computing clusters (openMosix).\", \
                \"Experience in process simulation and network modeling (Omnet++, cnet).\" \
            ] \
        }, \
        { \
            \"title\": \"Misc\", \
            \"feat\": [ \
                \"Office automation: Libre/OpenOffice, LaTeX, Doxygen, linuxdoc, MSOffice.\", \
                \"Graphic/Audio/Video editing: The Gimp, Inkscape, LibreCad, Avidemux, Audacity, DVD Authoring.\" \
            ] \
        } \
    ] \
}";
static const char *json_misc = "{
    \"misc\": { \
        \"languages\": [ \
            { \
                \"title\": \"Italian\", \
                \"value\": \"Maternal language.\" \
            }, \
            { \
                \"title\": \"English\", \
                \"value\": \"Good knowledge in reading, writing and speaking.\" \
            }, \
  	    { \
                \"title\": \"French\", \
                \"value\": \"Good knowledge in reading, writing and speaking.\" \
            } \
       ] \
    }, \
    \"interest\": \"I love music in all its forms and expressions, I delight in playing clarinet, guitar and keyboards, and singing in a country band (<a href='http://markyjeans.wordpress.com'>Marky Jeans</a>). I like mountain hiking, jogging on the beach and picnics with my family. I spread the culture and ethics of Free Software organizing LinuxDay in my hometown since 2002 and designing computer labs in schools. I love to cook and experiment with ingredients, flavors and spices.\" \
}";
#endif
