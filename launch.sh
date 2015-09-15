#!/bin/sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/restful-server/:$PWD/tcc/lib/tcc/:$PWD/sundown/

./tcc/bin/tcc -run  -I restful-server/ -Isundown/src/ -Isundown/html/ -Lrestful-server/ -Lsundown/ -lfossa -lsundown restful-server/restful_server.c 
