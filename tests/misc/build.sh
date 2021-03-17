#!/bin/sh
odir=/Code/omni
tdir=${odir}/tests
if [ "$1" = "heavy" ]; then
    flags="-DNDEBUG -D_CONSOLE -D_UNICODE -DUNICODE -DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO -DOMNI_SAFE_LIBRARY -DOMNI_NON_PORTABLE"
    cmd="g++ ${tdir}/misc/base.cpp ${odir}/source/library.cpp ${flags} -I${odir}/source -fexceptions -O3 -o${tdir}/bin/base"
    echo ${cmd}
    eval ${cmd}
else
    flags="-DOMNI_NON_PORTABLE";
    cmd="g++ ${tdir}/misc/base.cpp ${odir}/source/library.cpp ${flags} -I${odir}/source -fexceptions -O3 -o${tdir}/bin/base"
    echo ${cmd} $*
    eval ${cmd} $*
fi
