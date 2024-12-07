#!/bin/bash
#omni_lib_loc=/code/Zeriph/libraries/omni
omni_lib_loc=/Code/omni
docdir=${omni_lib_loc}/tools/docugen
zloc=${omni_lib_loc}/source
zsrc=${zloc}/library.cpp
# we can use C++03, but it seems that c++11 runs faster
cppstd="c++11"
gcc="clang++"
gexf="-std=${cppstd} -pthread -fexceptions -Werror"
zexf="-DOMNI_NON_PORTABLE -DOMNI_ENABLE_CXX"
zop="-O3"
zout="${docdir}/bin/docugen.bin"

parse_args()
{
    tmpuvar="-u"
    while [ "$*" != "" ]; do
        case $1 in
            "-dbg")
                zop="-DDOC_DEBUG -g"; zout="${docdir}/bin/debug_docugen.bin" ;;
            "-gcc") gcc="g++" ;;
            # other options
            "-d")
                zexf="${zexf} -D${2}"
                shift ;;
        esac
        shift
    done
    eopts="${eopts} ${tmpuvar}"
}

parse_args "$@"

sdir=${docdir}/src
xfiles="${sdir}/main.cpp ${sdir}/externs.cpp ${sdir}/gen.cpp ${sdir}/html.cpp ${sdir}/mti.cpp ${sdir}/parse.cpp ${sdir}/util.cpp"
incs="-I${zloc} -I${sdir}"
cmd="${gcc} ${xfiles} ${zsrc} ${incs} ${gexf} ${zexf} ${zop} -o ${zout}"
echo "${cmd}"
eval ${cmd}
if [ -f ${zout} ]; then
    echo "chmod 755 ${zout}"
    chmod 755 ${zout}
fi
