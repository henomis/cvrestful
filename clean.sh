#!/bin/sh
rm -fr tcc/*
rm -fr sundown
rm -fr restful-server/libfossa.so
make clean -C restful-server
