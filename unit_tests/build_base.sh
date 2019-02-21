#!/bin/sh
cmd="g++ base.cpp ../source/library.cpp -obin/base -DNDEBUG -D_CONSOLE -D_UNICODE -DUNICODE -DOMNI_UT_FULL -DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO -DOMNI_SAFE_FRAMEWORK -DOMNI_NON_PORTABLE -DOMNI_COMPILE_FLAGS -I../source -I. -fexceptions -O3"
echo ${cmd}
eval ${cmd}
