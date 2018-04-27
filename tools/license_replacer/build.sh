#!/bin/bash
d=`pwd`
o="/Code/omni/source"
cmd="g++ replacer.cpp ${o}/library.cpp -I${o} -O3 -DOMNI_NON_PORTABLE -fexceptions -o ${d}/bin/replacer"
echo ${cmd}
eval ${cmd}
