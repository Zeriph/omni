#!/bin/bash

omni=/Code/omni/source

do_build()
{
    echo "Building ${cpp}"
    cpp=$1
    cmd="g++ ${cpp} -o ../bin/solos/${cpp%.*} -g -O0 -I${omni} -DOMNI_NO_EXTERN_CONSTS -DOMNI_SAFE_LIBRARY -DOMNI_NON_PORTABLE -DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO"
    #echo ${cmd}
    eval ${cmd}
}

build_file()
{
    cpp=$1
    if [ -f ${cpp} ]; then
        do_build "${cpp}"
    else
        echo "File not found ${cpp}"
    fi
}

build_test()
{
    hpp=$1
    hpp="${hpp/$omni\//}"
    cpp="${hpp//\//_}"
    cpp="${cpp%.*}.cpp"
    if [ -f "${cpp}" ]; then
        do_build "${cpp}"
    else
        echo "Test does not exist: ${cpp}"
    fi
}

if [ "$1" = "all" ]; then
    for TEST in `find . -type f -name "*.cpp" | sort`; do
        build_file "${TEST/.\//}"
    done
elif [ "$1" = "solo" ]; then
    build_file "$2"
elif [ "$1" = "clean" ]; then
    rm -rfv ../bin/solos/omni_*
else
    build_test "$1"
fi
