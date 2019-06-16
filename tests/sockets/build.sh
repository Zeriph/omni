#!/bin/sh
odir=/Code/omni
tdir=${odir}/tests
flags="-DNDEBUG -D_CONSOLE -D_UNICODE -DUNICODE -DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO -DOMNI_SAFE_FRAMEWORK  -DOMNI_NON_PORTABLE -I../../source -I. -fexceptions -O3"
c="g++ ${tdir}/sockets/client.cpp ${odir}/source/library.cpp -o${tdir}/bin/client ${flags}"
s="g++ ${tdir}/sockets/server.cpp ${odir}/source/library.cpp -o${tdir}/bin/server ${flags}"
l="g++ ${tdir}/sockets/local.cpp ${odir}/source/library.cpp -o${tdir}/bin/local ${flags}"
echo ${l} $*
eval ${l} $*
echo ${s} $*
eval ${s} $*
echo ${c} $*
eval ${c} $*
