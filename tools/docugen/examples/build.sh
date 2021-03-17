#!/bin/sh
#omni_lib_loc=/code/Zeriph/libraries/omni
omni_lib_loc=/Code/omni
exdir=${omni_lib_loc}/tools/docugen/examples/classes
fwexd=${omni_lib_loc}/tools/docugen/examples/library
zloc=${omni_lib_loc}/source
zsrc=${zloc}/library.cpp
exname=$1
exname=${exname//.cpp}
zout="${omni_lib_loc}/tools/docugen/bin/examples/${exname}"
xfile="${exdir}/${exname}.cpp"
zexd="-DOMNI_SHOW_DEBUG=5 -DOMNI_SHOW_DEBUG_ERR -DOMNI_SHOW_DEBUG_FILE -DOMNI_SHOW_DEBUG_FUNC -DOMNI_SHOW_DEBUG_LINE"
zexf="-DOMNI_UT_FULL -DOMNI_SHOW_DEBUG=5 -DOMNI_SHOW_DEBUG_ERR -DOMNI_SHOW_DEBUG_FILE -DOMNI_SHOW_DEBUG_FUNC -DOMNI_SHOW_DEBUG_LINE -DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO -DOMNI_SAFE_LIBRARY -DOMNI_NON_PORTABLE"

if [ "$1" == "list" ]; then
    find ${exdir} -type f -name "*.cpp" -exec basename "{}" ";"
    exit 0
elif [ "$1" == "html" ]; then
    xfile="${fwexd}/index_html.cpp"
elif [ "$1" == "fw" ]; then
    if [ "$2" == "list" ]; then
        tname=`basename ${fwexd}`
        find ${fwexd}/ -type d -exec basename "{}" ";" | grep -v ${tname}
        exit 0
    fi
    xfile="${fwexd}/$2/example.cpp"
fi

if [ ! -f ${xfile} ]; then
    echo "Example file not found: ${xfile}"
    exit 0
fi
if [ "$2" == "debug" ]; then
    echo "Invoking: g++ ${xfile} ${zsrc} -I${zloc} ${zexd} -o ${zout} -pthread"
    g++ ${xfile} ${zsrc} -I${zloc} ${zexd} -o ${zout} -pthread
elif [ "$2" == "full" ]; then
    echo "Invoking: g++ ${xfile} ${zsrc} -I${zloc} ${zexf} -o ${zout} -pthread"
    g++ ${xfile} ${zsrc} -I${zloc} ${zexf} -o ${zout} -pthread
elif [ "$2" == "nolib" ]; then
    echo "Invoking: g++ ${xfile} -I${zloc} -o ${zout} -pthread"
    g++ ${xfile} -I${zloc} -o ${zout} -pthread
elif [ "$2" == "fullnl" ]; then
    echo "Invoking: g++ ${xfile} -I${zloc} ${zexf} -o ${zout} -pthread"
    g++ ${xfile} -I${zloc} ${zexf} -o ${zout} -pthread
elif [ "$2" == "lrt" ]; then
    echo "Invoking: g++ ${xfile} ${zsrc} -I${zloc} -o ${zout} -pthread -lrt"
    g++ ${xfile} ${zsrc} -I${zloc} -o ${zout} -pthread -lrt
else
    echo "Invoking: g++ ${xfile} ${zsrc} -I${zloc} -o ${zout} -pthread"
    g++ ${xfile} ${zsrc} -I${zloc} -o ${zout} -pthread
fi
