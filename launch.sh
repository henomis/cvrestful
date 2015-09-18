#!/bin/sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/restful-server/:$PWD/tcc/lib/tcc/:$PWD/sundown/


PREFIX=""
COMMAND="./tcc/bin/tcc -run  -I restful-server/ -Isundown/src/ -Isundown/html/ -Lrestful-server/ -Lsundown/ -lfossa -lsundown restful-server/restful_server.c"

if [ $1 ];  then
	PREFIX="sudo -u $1 "
	COMMAND="$PREFIX$COMMAND"
	
	while true; do
		eval $COMMAND
		sleep 1
	done

else
	`$COMMAND`
fi




