#!/bin/sh

#omni_lib_loc=/code/Zeriph/libraries/omni
omni_lib_loc=/Code/omni

check_omni_lib_loc()
{
    while [ "$*" != "" ]; do
        case $1 in
            "-odir") omni_lib_loc="${2}"; shift ;;
        esac
        shift
    done
    if [ ! -d ${omni_lib_loc} ]; then
        echo "Omni Library location not found: ${omni_lib_loc}"
        echo "Specify the Omni Library path with the -odir option"
        exit 0
    fi
}

check_omni_lib_loc $*

binfldr="${omni_lib_loc}/tests/bin"
utloc="${omni_lib_loc}/tests/unit/units"
unit_tests=""
for utf in ${utloc}/*.hpp; do
    tname=${utf#$utloc/}
    tname=${tname%".hpp"}
    unit_tests="${unit_tests} ${tname}"
done

eopts=""
utest="all"
tmput="all"
utestflag=""
vs=""
llog=""
sys_type="bsd"
edefs=""
use_log=0
noopt=0
is32bit=0
toolchain=g++
force_test=0

usage()
{
    echo "usage: utnix [system] [test] [flags]"
    echo 
    echo "SYSTEM:"
    echo " The [system] value specified will determine on what type of system to compile"
    echo " on. Valid values are bsd, nix, osx, and qnx"
    echo
    echo "FLAGS:"
    echo " Valid flags that can be passed to the compile script are as follows:"
    echo
    echo "compile script options:"
    echo "       -?          Display this help"
    echo "       -c [opts]   Pass extra arguments to the compiler"
    echo "       -d [define] Pass extra defines to the compiler"
    echo "       -i [path]   Includes [path] in the compiler include path"
    echo "       -out [path] The output build path to put the lib/bin/obj/asm files"
    echo "       -v          This flag signifies the verbosity level of the compiler"
    echo "                   output. Valid '-v' values are as follows:"
    echo "                   -v          = Verbose level 1 (basic output)"
    echo "                   -vv/-v2     = Verbose L2 (show more output)"
    echo "                   -vvv/-v3    = Verbose L3 (show ALL output)"
    echo "       -single     Builds library.cpp"
    echo "       -lib        Builds omni.a then links against it for the unit tests"
    echo "       -log        Log the output to the logs folder"
    echo "       -po         Parse the compile script only"
    echo 
    echo "library options:"
    echo "       -lite       Sets the OMNI_LITE macro definition"
    echo "       -heavy      Sets the heavy object flag"
    echo "       -uni        Sets the UNICODE flags (builds using unicode)"
    echo "       -no [op]    Passes along a 'no-flag' to the compile script"
    echo "       -safe       Sets the OMNI_SAFE_LIBRARY macro definition"
    echo "       -sfw [op]   Set the OMNI_SAFE_[op] macro definition"
    echo "       -np         Sets the OMNI_NON_PORTABLE compiler flag and enables"
    echo "                   compilation of 'non-portable' code"
    echo "       -terr       Sets the OMNI_TERMINATE macro"
    echo 
    echo "library debug options:"
    echo "       -d1         Sets the OMNI_SHOW_DEBUG=1"
    echo "       -d2         Sets the OMNI_SHOW_DEBUG=2"
    echo "       -d3         Sets the OMNI_SHOW_DEBUG=3"
    echo "       -d4         Sets the OMNI_SHOW_DEBUG=4"
    echo "       -d5         Sets the OMNI_SHOW_DEBUG=5"
    echo "       -derr       Sets OMNI_SHOW_DEBUG_ERR"
    echo "       -dfull      Sets OMNI_SHOW_DEBUG_FILE, OMNI_SHOW_DEBUG_FUNC andOMNI_SHOW_DEBUG_LINE"
    echo "       -dbgX       equivalent to -dX -dfull"
    echo
    echo "compiler options:"
    echo "       -tc [tc]    Sets the compiler/toolchain to use (default of g++)"
    echo "       -lc [lc]    Sets the library toolchain when -lib specified (default of ar)"
    echo "       -effc       Sets the -Weffc++ flag which warns about style guidlines"
    echo "                   violations from Scott Meyers' Effective C++ book"
    echo "       -we         Treat all warnings as errors"
    echo "       -se         Stop on first error (instead of trying to continue)"
    echo "       -stats      Sets the -Q flag when compiling which shows statistics of the"
    echo "                   compilation unit"
    echo "       -pe         Sets the -pedantic-errors flag"
    echo "       -lrt        Some platforms need the 'rt' library to compile, this sets the"
    echo "                   -lrt compiler/linker flag to compile/link against the 'rt' libs"
    echo "       -nopthread  Disables the -pthread compiler/linker flag"
    echo "       -nortti     Disables RTTI (run-time type information) for C++"
    echo "       -noopt      No optimizations (default of -opt 3)"
    echo "       -opt [op]   Enable global optimization based on 0,1,2,3 or s"
    echo "       -asm        Generate the assembly output (.s file)"
    echo "       -gdb        Sets the -ggdb flag, enabling GDB debug output (for certain compilers)"
    echo "       -g          Sets the -g flag, enabling GDB debug output (for certain compilers)"
    echo "       -3          Specifying this will enable 32-bit compilation"
    echo "       -syntax     Sets the -fsyntax-only flag which checks the code for syntax"
    echo "                   errors only and does nothing beyond that"
    echo "       -eo         Use the extra compiler/linker flags (can generate erroneous errors)"
    echo "       -pad        Use the -Wpadded (can generate erroneous errors)"
    echo "       -std [std]  Compiles the code according to the standard defined by [std]"
}

list_tests()
{
    echo "Current tests available:"
    for test in ${unit_tests}; do
        echo "- ${test}"
    done
}

parse_set_test()
{
    utest=$1
    utupper=`echo ${utest} | tr [a-z] [A-Z]`
    utestflag="OMNI_UT_${utupper}"
    if [ "$1" = "full" ]; then
        eopts="${eopts} -oo heavy"
        eopts="${eopts} -oo safe fw"
        eopts="${eopts} -oo np"
    fi
}

parse_test()
{
    if [ $force_test -eq 1 ]; then
        parse_set_test "$1"
    else
    
        ut=""
        for test in ${unit_tests}; do
            if [ $1 = $test ]; then
                ut=$1
                break
            fi
        done
        if [ "$ut" = "" ]; then
            if [ -f ${utloc}/$1.hpp ]; then
                echo "Empty unit test specified; this might indicate a shell escape issue"
            else
                echo "Could not find unit test for '$1' at '${utloc}/$1.hpp'"
                list_tests
            fi
            #usage
            exit 0
        else
            parse_set_test "$ut"
        fi
    
    fi
}

parse_args()
{
    tmpuvar="-u"
    while [ "$*" != "" ]; do
        case $1 in
            "nix") sys_type="nix" ;; #; eopts="${eopts}" ;;
            "obsd") sys_type="bsd"; eopts="${eopts} -d OMNI_NO_CSTDINT" ;;
            "bsd") sys_type="bsd" ;; #; eopts="${eopts} -tc c++" ;;
            "osx") sys_type="osx" ;; #; eopts="${eopts} -tc clang++" ;;
            # QNX needs special attention (nopthread because it links automagically)
            "qnx") sys_type="qnx"; eopts="${eopts} -co nopthread -d OMNI_CLOCK_GETRES_REALTIME" ;;
            
            # compile.sh script options
            "-out")
                eopts="${eopts} -out ${2}"
                binfldr="${2}/bin"
                shift ;;
            "-c") eopts="${eopts} -c ${2}"; shift ;;
            "-d") edefs="${edefs} -d ${2}"; shift ;;
            "-i") edefs="${edefs} -i ${2}"; shift ;;
            "-single") eopts="${eopts} -single" ;;
            "-lib") eopts="${eopts} -lib" ;;
            "-log") use_log=1 ;;
            "-tc") 
                toolchain="${2}"
                eopts="${eopts} -tc ${2}"
                shift ;;
            "-lc") eopst="${eopts} -lc ${2}"; shift ;;
            "-v") vs="-v" ;;
            "-vv") vs="-vv" ;;
            "-vvv") vs="-vvv" ;;
            "-v2") vs="-vv" ;;
            "-v3") vs="-vvv" ;;
            "-po") eopts="${eopts} -po" ;;
            "-?") usage; exit 0 ;;
            "-help") usage; exit 0 ;;
            "-list") list_tests; exit 0 ;;

            # library options
            "-lite") eopts="${eopts} -oo lite" ;;
            "-heavy") eopts="${eopts} -oo heavy" ;;
            "-uni") eopts="${eopts} -oo uni" ;;
            "-no") eopts="${eopts} -oo no ${2}"; shift ;;
            "-safe") eopts="${eopts} -oo safe fw" ;;
            "-sfw") eopts="${eopts} -oo safe ${2}"; shift ;;
            "-np") eopts="${eopts} -oo np" ;;
            "-terr") eopts="${eopts} -oo terr" ;;
            "-c++11") eopts="${eopts} -d OMNI_ENABLE_CXX" ;;
            
            # library debug options
            "-d1") eopts="${eopts} -dbg 1" ;;
            "-d2") eopts="${eopts} -dbg 2" ;;
            "-d3") eopts="${eopts} -dbg 3" ;;
            "-d4") eopts="${eopts} -dbg 4" ;;
            "-d5") eopts="${eopts} -dbg 5" ;;
            "-derr") eopts="${eopts} -dbg err" ;;
            "-dfull") eopts="${eopts} -dbg full" ;;
            "-dbg1") eopts="${eopts} -dbg 1 -dbg full" ;;
            "-dbg2") eopts="${eopts} -dbg 2 -dbg full" ;;
            "-dbg3") eopts="${eopts} -dbg 3 -dbg full" ;;
            "-dbg4") eopts="${eopts} -dbg 4 -dbg full" ;;
            "-dbg5") eopts="${eopts} -dbg 5 -dbg full" ;;
            
            # compiler options
            "-effc") eopts="${eopts} -co effc" ;;
            "-we") eopts="${eopts} -co we" ;;
            "-se") eopts="${eopts} -co se" ;;
            "-stats") eopts="${eopts} -co stats" ;;
            "-pe") eopts="${eopts} -co pe" ;;
            "-lrt") eopts="${eopts} -co lrt" ;;
            "-nopthread") eopts="${eopts} -co nopthread" ;;
            "-nortti") eopts="${eopts} -co nortti" ;;
            "-noopt") noopt=1 ;;
            "-opt") eopts="${eopts} -co opt ${2}" ;;
            "-asm") eopts="${eopts} -co asm" ;;
            "-gdb")
                eopts="${eopts} -co gdb"
                tmpuvar="" ;;
            "-g")
                eopts="${eopts} -co dbg"
                tmpuvar="" ;;
            "-3") is32bit=1 ;;
            "-std") eopts="${eopts} -co std ${2}"; shift ;;
            "-syntax") eopts="${eopts} -co syntax" ;;
            "-eo") eopts="${eopts} -co xtra" ;;
            "-pad") eopts="${eopts} -co pad" ;;
            "-force") force_test=1 ;;
            "-odir") shift ;;
            *) tmput=$1 ;;
        esac
        shift
    done
    eopts="${eopts} ${tmpuvar}"
}

parse_args "$@"
parse_test $tmput

if [ $is32bit -eq 1 ]; then
    eopts="${eopts} -co libop elf32-i386 -c -m32"
    if [ "${sys_type}" == "osx" ]; then
        eopts="${eopts} -c -Xlinker -c -arch -c -Xlinker -c i386"
    else
        eopts="${eopts} -c -Xlinker -c -melf_i386"
    fi
fi

if [ "${sys_type}" = "osx" ]; then
    eopts="${eopts} -co nopthread"
fi

if [ $use_log -eq 1 ]; then
    llog="-log ${omni_lib_loc}/tests/logs/${sys_type}_build.log"
    elog="-elog ${omni_lib_loc}/tests/logs/${sys_type}_error.log"
fi

if [ $noopt -eq 0 ]; then
    eopts="${eopts} -co opt 0"
fi

utofile="${binfldr}/${sys_type}_test"
utdef="-s ${omni_lib_loc}/tests/unit/main.cpp -i ${omni_lib_loc}/tests/unit -d ${utestflag}"

cpopt="${omni_lib_loc}/tests/unit/compile.sh ${utdef} -o ${utofile} -fw ${omni_lib_loc} ${eopts} ${edefs} ${vs} ${llog} ${elog}"
echo "sh ${cpopt}"
eval "sh ${cpopt}"
