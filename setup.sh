#!/bin/sh

PREFIX=$PWD

# download and decompress tinyc
wget -c http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26.tar.bz2 -O tcc-0.9.26.tar.bz2 && tar vxfj tcc-0.9.26.tar.bz2 && rm -fr tcc-0.9.26.tar.bz2 && cd tcc-0.9.26 && ./configure --prefix=$PREFIX/tcc && make && make install && cd .. && rm -fr tcc-0.9.26 && make -C restful-server
