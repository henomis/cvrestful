#!/bin/sh

PREFIX=$PWD

# download and decompress tinyc
wget -c http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.26.tar.bz2 -O tcc-0.9.26.tar.bz2 && 
tar vxfj tcc-0.9.26.tar.bz2 && 
rm -fr tcc-0.9.26.tar.bz2 && 
cd tcc-0.9.26 && 
./configure --prefix=$PREFIX/tcc && 
make && 
make install && 
cd .. && 
rm -fr tcc-0.9.26 && 
wget -c https://github.com/vmg/sundown/archive/master.zip -O sundown.zip && 
unzip sundown.zip && 
rm -fr sundown.zip &&
mv sundown-master sundown &&  
cat sundown/Makefile|sed 's/-Wl//g' > sundown/Makefile.linux &&
make -C sundown -f Makefile.linux &&
make -C restful-server
