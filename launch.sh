#!/bin/sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/restful-server/:$PWD/tcc/lib/tcc/

./tcc/bin/tcc -run  -I restful-server/ -Lrestful-server/ -lfossa restful-server/restful_server.c
