#!/bin/sh


# TODO: clean up this script (get rid of the OMNI_X options and figure out an easier way to do that)
# TODO: ensure all compiler options are included

#-Weffc++ (C++ only)
# Warn about violations of the following style guidelines from Scott
# Meyers' Effective C++ book:
# *   Item 11:  Define a copy constructor and an assignment operator
#   for classes with dynamically allocated memory.
# *   Item 12:  Prefer initialization to assignment in constructors.
# *   Item 14:  Make destructors virtual in base classes.
# *   Item 15:  Have "operator=" return a reference to *this.
# *   Item 23:  Don't try to return a reference when you must return an object.
# Also warn about violations of the following style guidelines from
# Scott Meyers' More Effective C++ book:
# *   Item 6:  Distinguish between prefix and postfix forms of increment and decrement operators.
# *   Item 7:  Never overload "&&", "||", or ",".
# When selecting this option, be aware that the standard library
# headers do not obey all of these guidelines; use grep -v to filter
# out those warnings.

# -Wextra is the same as -W
# -ansi -Wextra -Wall -Wold-style-cast -Woverloaded-virtual -Wpointer-arith -Wcast-qual -Wcast-align -Waddress
# -Wswitch-default -Wswitch-enum -Wunused-parameter -Wfloat-equal -Wshadow -Wconversion -Wwrite-strings
# -Wmissing-field-initializers -Wpadded -Wredundant-decls -Wunreachable-code -Wvolatile-register-var
# -Wctor-dtor-privacy -Wnon-virtual-dtor -Wsign-promo -Wreorder -Wno-pmf-conversions
# note: -Wc++-compat is for C/Obj-C only
# note: -Waggregate-return can be a valid concern, but is largely erroneous (especially where Omni is concenred)

# (C only)
# -Wtraditional -Wdeclaration-after-statement -Wbad-function-cast -Wstrict-prototypes -Wold-style-definition
# -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wpointer-sign

# Some platforms need to compile/link against the 'rt' libs (-lrt):
# Debian/RoboLinux, Slackware/PuppyLinux, Linux Mint, Ubuntu/ElementaryOS, RHEL/CentOS/Fedora, PCLinuxOS
# Note that some new versions of the same platforms (Fedora/Cent) don't require -lrt

# Note for Solaris/SUN: issues running unit tests from the mounted smbfs share. After unit
# test was copied to the local drive, however, test ran fine; possible network access issue

# curdate=`date "+%Y-%m-%d %H:%M:%S"`
# echo "Build started: ${curdate}"

omni_lib_loc=/code/Zeriph/libraries/omni

check_omni_lib_loc()
{
    while [ "$*" != "" ]; do
        case $1 in
            "-fw") omni_lib_loc="${2}"; shift ;;
        esac
        shift
    done
    if [ ! -d ${omni_lib_loc} ]; then
        echo "Omni Library location not found: ${omni_lib_loc}"
        echo "Specify the Omni Library path with the -fw option"
        exit 0
    fi
}

check_omni_lib_loc $*

common="${omni_lib_loc}/source"
odir="${omni_lib_loc}/build"
defines=""
toolchain=g++
libchain=ar
prog=main
source=
# could do a `ls`, etc. but this ensures the source I want
# compiled (kind of forcing a double check of your work)
fwsrc="${common}/application.cpp"
fwsrc="${fwsrc} ${common}/argparser.cpp"
fwsrc="${fwsrc} ${common}/async_timer.cpp"
fwsrc="${fwsrc} ${common}/basic_thread.cpp"
fwsrc="${fwsrc} ${common}/binary_semaphore.cpp"
fwsrc="${fwsrc} ${common}/conditional.cpp"
fwsrc="${fwsrc} ${common}/drop_timer.cpp"
fwsrc="${fwsrc} ${common}/environment.cpp"
fwsrc="${fwsrc} ${common}/externs.cpp"
fwsrc="${fwsrc} ${common}/io.cpp"
# fwsrc="${fwsrc} ${common}/filesystemwatcher.cpp # incomplete
fwsrc="${fwsrc} ${common}/mutex.cpp"
# fwsrc="${fwsrc} ${common}/net_util.cpp # incomplete
fwsrc="${fwsrc} ${common}/queue_timer.cpp"
fwsrc="${fwsrc} ${common}/runnable.cpp"
fwsrc="${fwsrc} ${common}/semaphore.cpp"
# fwsrc="${fwsrc} ${common}/socket.cpp # incomplete
# fwsrc="${fwsrc} ${common}/tcp.cpp # incomplete
# fwsrc="${fwsrc} ${common}/udp.cpp # incomplete
fwsrc="${fwsrc} ${common}/stopwatch.cpp"
fwsrc="${fwsrc} ${common}/sync_timer.cpp"
fwsrc="${fwsrc} ${common}/system.cpp"
fwsrc="${fwsrc} ${common}/thread.cpp"
fwsrc="${fwsrc} ${common}/threadpool.cpp"
fwsrc="${fwsrc} ${common}/version.cpp"
includes="-I${common}"
extraopts=""
#log_file="${omni_lib_loc}/build/logs/build.log"
#err_log_file="${omni_lib_loc}/build/logs/error.log"
log_file=""
err_log_file=""
verbose=0
docleanup=0
has_debug=0
no_console=0
fexcep="-fexceptions"
parse_only=0
syntax_only=0
nopthread=0
useuni=1
doasm=0
islib=0
libops="rvs"

####### START FUNCTIONS #######

msg()
{
	echo "${1}"
	if [ "$log_file" != "" ]; then
		echo "${1}" >> ${log_file}
	fi	
}

msgv()
{
    if [ $verbose -ge $1 ]; then
        msg "$2"
    fi
}

msgp()
{
    msgv $1 "$2"
    if [ $parse_only -eq 0 ]; then
        eval "$2"
    fi    
}

usage()
{
	echo "usage: compile [options]"
	echo
	echo "OPTIONS:"
    echo
    echo "compile script options:"
	echo "       -s [source] The main source file(s) to compile (files other than"
	echo "                   the framework source). If this flag is not set, this"
	echo "                   script will build Omni as a library."
	echo "                   Specified source must be enclosed in quotes \"\" and"
	echo "                   separated by spaces."
	echo "                   Example:"
	echo "                   compile -s \"file1.cpp file2.cpp file3.cpp\" -o main"
    echo "       -fw [path]  The Omni Framework path (default of '${omni_lib_loc}')"
    echo "       -out [path] The output build path to put the lib/bin/obj/asm files"
    echo "       -i [path]   Includes [path] in the compiler include path"
	echo "       -o [name]   The file you wish to compile (without an extension)"
	echo "       -c [opts]   Pass extra arguments to the compiler"
    echo "       -d [define] Pass extra defines to the compiler"
	echo "       -u          Specifying this will clean up any .o files"
    echo "       -single     Specifying this will build library.cpp (single file framework)"
    echo "       -lib        Specifying this will compile as a library instead of an executable"
    echo "       -log [log]  Write console output to a log file"
	echo "       -elog [log] Write the error log to [log], default"
	echo "       -v          Show verbose output (-v = 1, -vv = 2, -vvv = 3)"
	echo "       -po         Parse the compile script only"
    echo "       -oo [ops]   Enables framework features"
    echo "       -dbg [ops]  Enables framework debug features"
    echo "       -co [ops]   Enables compiler/linker features"
    echo "       -tc [tc]    specify the compiler/toolchain to use (default of '${toolchain}')"
    echo "       -lc [lc]    specify the library build system to use (default of '${libchain}')"
    echo
    echo "framework options (-oo):"
	echo "       lite        Defines the OMNI_LITE flag which trims down the code and gets rid"
	echo "                   of some functionality"
    echo "       heavyo      Defines the OMNI_DISPOSE_EVENT, OMNI_OBJECT_NAME and OMNI_TYPE_INFO macros"
    echo "       sfall       Defines the OMNI_SAFE_FRAMEWORK flag which enables all 'safe' flags"
    echo "       sfapp       Defines the OMNI_SAFE_APPLICATION flag which sets omni::application thread safe"
	echo "       sfev        Defines the OMNI_SAFE_EVENTS flag which says omni::event's are thread safe"
    echo "       sfdg        Defines the OMNI_SAFE_DELEGATES flag which says omni::delegate's are thread safe"
    echo "       sftmr       Defines the OMNI_SAFE_TIMER flag which says omni::timers's are not thread safe"
    echo "       sfsem       Defines the OMNI_SAFE_SEMAPHORE flag which says omni::semeaphore's are thread safe"
    echo "       sfmtx       Defines the OMNI_SAFE_MUTEX flag which says omni::sync::mutex are thread safe"
    echo "       sfcond      Defines the OMNI_SAFE_CONDITIONAL flag which says omni::sync::conditional are thread safe"
    echo "       sfthread    Defines the OMNI_SAFE_THREAD flag which says omni::sync::thread are thread safe"
    echo "       sfrunnable  Defines the OMNI_SAFE_RUNNABLE_THREAD flag which says omni::sync::runnable_thread's are thread safe"
    echo "       np          Sets the OMNI_NON_PORTABLE compiler flag and enables"
    echo "                   compilation of 'non-portable' code"
    echo "       noexcep     Defines the OMNI_NO_THROW flag and the -fno-exceptions"
	echo "                   compiler and linker flag"
    echo "       nouni       Disables the UNICODE flags (does not build using unicode)"
    echo "       terr        Defines the OMNI_TERMINATE macro"
    echo "       disposing   Defines the OMNI_DISPOSE_EVENT macro"
    echo "       objname     Defines the OMNI_OBJECT_NAME macro"
    echo "       typeinfo    Defines the OMNI_TYPE_INFO macro"
    echo "       stdcall     Defines the thread calling convention to be __attribute__((stdcall))"
    echo "       fastcall    Defines the thread calling convention to be __attribute__((fastcall))"
    echo "       cdecl       Defines the thread calling convention to be __attribute__((cdecl))"
    echo
    echo "framework debug options (-dbg):"
    echo "       1           Defines the OMNI_SHOW_DEBUG=1"
    echo "       2           Defines the OMNI_SHOW_DEBUG=2"
    echo "       3           Defines the OMNI_SHOW_DEBUG=3"
    echo "       4           Defines the OMNI_SHOW_DEBUG=4"
    echo "       5           Defines the OMNI_SHOW_DEBUG=5"
    echo "       err         Defines the OMNI_SHOW_DEBUG_ERR"
    echo "       file        Defines the OMNI_SHOW_DEBUG_FILE"
    echo "       func        Defines the OMNI_SHOW_DEBUG_FUNC"
    echo "       line        Defines the OMNI_SHOW_DEBUG_LINE"
    echo
    echo "compiler options (-co):"
    echo "       effc        Sets the -Weffc++ flag which warns about style guidelines"
	echo "                   violations from Scott Meyers' Effective C++ book"
    echo "       we          Treat all warnings as errors"
	echo "       se          Stop on first error (instead of trying to continue)"
    echo "       stats       Sets the -Q flag when compiling which shows statistics of the"
    echo "                   compilation unit"
    echo "       ep          Sets the -pedantic-errors flag"
    echo "       lrt         Some platforms need the 'rt' library to compile, this sets the"
    echo "                   -lrt compiler/linker flag to compile/link against the 'rt' libs"
    echo "       nopthread   Disables the -pthread compiler/linker flag"
	echo "       xtra        Use the extra compiler/linker flags (can generate erroneous errors)"
    echo "       nortti      Disables RTTI (run-time type information) for C++"
    echo "       opti        Enable global optimization with intrinsic functions (-O)"
    echo "       opt1        Enable optimizations (-O1)"
    echo "       opt2        Enable more optimizations (-O2)"
    echo "       opt3        Maximum optimizations (-O3)"
    echo "       opts        Favor code space (-Os)"
    echo "       asm         Generate the assembly output (.s file)"
    echo "       ggdb        Sets the -ggdb flag, enabling GDB debug output (for certain compilers)"
    echo "       gdb         Sets the -g flag, enabling GDB debug output (for certain compilers)"
    echo "       libop [op]  Specifies a library build option"
    echo "       noconsole   Specifies to not define the _CONSOLE flag"
    echo "       syntax      Sets the -fsyntax-only flag which checks the code for syntax"
    echo "                   errors only and does nothing beyond that"
    echo "       std [std]   Compiles the code according to the standard defined by [std]"
    echo "                   valid values are as follows:"
    echo "                      c89"
    echo "                      iso9899:1990"
    echo "                      iso9899:199409"
    echo "                      c99"
    echo "                      iso9899:1999"
    echo "                      gnu89"
    echo "                      gnu99"
    echo "                      c++98"
    echo "                      gnu++98"
    echo
    echo "Note: since certain portions of Omni are header only, due to template specializations"
    echo "and other C++ specific issues, if you compile Omni as a library with certain preprocessor"
    echo "options on, remember to keep those same options defined when building your other source"
    echo "that references the Omni library. Not doing this can result in undefined behavior (see"
    echo "the virtual thunk note)."
}

parse_args()
{
	while [ "$*" != "" ]; do
        case $1 in
            "-s") source="${source} ${2}"; shift ;;
            "-out") odir="${2}"; shift ;;
            "-fw") omni_lib_loc="${2}"; shift ;;
            "-i")
                incld=${2}/
                incld=$(echo $incld | tr "//" "/")
                incld=$(echo $incld | tr "//" "/")
                includes="${includes} -I${incld}"
                ;;
            
            "-o") prog=$2; shift  ;;
            "-c") extraopts="${extraopts} ${2}"; shift ;;
            "-d") defines="${defines} -D${2}"; shift ;;
            "-u") docleanup=1 ;;
            "-single") fwsrc=${common}/library.cpp ;;
            "-lib") islib=1 ;;
            "-tc") toolchain="${2}"; shift ;;
            "-lc") libchain="${2}"; shift ;;
            "-log") log_file=$2; shift ;;
            "-elog") err_log_file=$2; shift ;;
            "-v") verbose=1 ;;
            "-vv") verbose=2 ;;
            "-vvv") verbose=3 ;;
            "-po") parse_only=1 ;;
            "-?") usage; exit 0 ;;
            "-oo")
                # framework options
                case $2 in
                    "lite") defines="${defines} -DOMNI_LITE" ;;
                    "heavyo") defines="${defines} -DOMNI_DISPOSE_EVENT -DOMNI_OBJECT_NAME -DOMNI_TYPE_INFO" ;;
                    "sfall") defines="${defines} -DOMNI_SAFE_FRAMEWORK" ;;
                    "sfapp") defines="${defines} -DOMNI_SAFE_APPLICATION" ;;
                    "sfev") defines="${defines} -DOMNI_SAFE_EVENTS" ;;
                    "sfdg") defines="${defines} -DOMNI_SAFE_DELEGATES" ;;
                    "sftmr") defines="${defines} -DOMNI_SAFE_TIMER" ;;
                    "sfsem") defines="${defines} -DOMNI_SAFE_SEMAPHORE" ;;
                    "sfthread") defines="${defines} -DOMNI_SAFE_THREAD" ;;
                    "sfrunnable") defines="${defines} -DOMNI_SAFE_RUNNABLE_THREAD" ;;
                    #define DOMNI_SAFE_PROP
                    "sfmtx") defines="${defines} -DOMNI_SAFE_MUTEX" ;;
                    "sfcond") defines="${defines} -DOMNI_SAFE_CONDITIONAL" ;;
                    "np") defines="${defines} -DOMNI_NON_PORTABLE" ;;
                    "noexcep")
                        defines="${defines} -DOMNI_NO_THROW"
                        fexcep="-fno-exceptions"
                        ;;
                    "nouni") useuni=0 ;;
                    "stdcall") defines="${defines} -DOMNI_THREAD_STDCALL" ;;
                    "fastcall") defines="${defines} -DOMNI_THREAD_FASTCALL" ;;
                    "cdecl") defines="${defines} -DOMNI_THREAD_CDECL" ;;
                    "terr") defines="${defines} -DOMNI_TERMINATE" ;;
                    "disposing") defines="${defines} -DOMNI_DISPOSE_EVENT" ;;
                    "objname") defines="${defines} -DOMNI_OBJECT_NAME" ;;
                    "typeinfo") defines="${defines} -DOMNI_TYPE_INFO" ;;
                    *) echo "Unknown framework option $2"; usage ;;
                esac
                shift
                ;;
            "-dbg")
                # framework debug options
                has_debug=1
                case $2 in
                    "1") defines="${defines} -DOMNI_SHOW_DEBUG=1" ;;
                    "2") defines="${defines} -DOMNI_SHOW_DEBUG=2" ;;
                    "3") defines="${defines} -DOMNI_SHOW_DEBUG=3" ;;
                    "4") defines="${defines} -DOMNI_SHOW_DEBUG=4" ;;
                    "5") defines="${defines} -DOMNI_SHOW_DEBUG=5" ;;
                    "err") defines="${defines} -DOMNI_SHOW_DEBUG_ERR" ;;
                    "file") defines="${defines} -DOMNI_SHOW_DEBUG_FILE" ;;
                    "func") defines="${defines} -DOMNI_SHOW_DEBUG_FUNC" ;;
                    "line") defines="${defines} -DOMNI_SHOW_DEBUG_LINE" ;;
                    *) echo "Unknown debug option $2"; usage ;;
                esac
                shift
                ;;
            "-co")
                # compiler options
                case $2 in
                    "effc")
                        extraopts="${extraopts} -Weffc++"
                        msg "Filter options: cat log | grep \"warning\" grep -v \"units\" | grep -v \"stl_deque\" | grep -v \"locale_facets.h\" | grep -v \"streambuf_\" | grep -v \"iosfwd\" | grep -v \"locale_classes\" | grep -v \"stl_vector\" | grep -v stl_pair | grep -v \"allocator.h\" | grep -v \"basic_string.h\" | grep -v \"codecvt.h\" | grep -v \"stl_iterator\" | grep -v \"stream_iterator\" | grep -v \"instantiated from\" | grep -v \"In instantiation\" | grep -v \"non-virtual destructor\" | grep -v \" from\" | grep -v \"property.hpp\""
                        ;;
                    "we") extraopts="${extraopts} -Werror" ;;
                    "se") extraopts="${extraopts} -Wfatal-errors" ;;
                    "stats") extraopts="${extraopts} -Q" ;;
                    "ep") extraopts="${extraopts} -pedantic-errors" ;;
                    "lrt") extraopts="${extraopts} -lrt" ;;
                    "nopthread") nopthread=1 ;;
                    "nortti") extraopts="${extraopts} -fno-rtti" ;;
                    "opti") extraopts="${extraopts} -O" ;;
                    "opt1") extraopts="${extraopts} -O1" ;;
                    "opt2") extraopts="${extraopts} -O2" ;;
                    "opt3") extraopts="${extraopts} -O3" ;;
                    "opts") extraopts="${extraopts} -Os" ;;
                    "noconsole") no_console=1 ;;
                    "asm") doasm=1 ;;
                    "ggdb")
                        extraopts="${extraopts} -ggdb"
                        docleanup=0
                        ;;
                    "gdb")
                        extraopts="${extraopts} -g"
                        docleanup=0
                        ;;
                    "libop")
                        libops="${libops} ${3}"
                        shift
                        ;;
                    "std")
                        extraopts="${extraopts} -std=${3}"
                        shift
                        ;;
                    "syntax")
                        syntax_only=1
                        extraopts="${extraopts} -fsyntax-only";
                        ;;
                    "xtra")
                        extraopts="${extraopts} -ansi -Wextra -Wall -Wold-style-cast -Woverloaded-virtual"
                        extraopts="${extraopts} -Wpointer-arith -Wcast-qual -Wcast-align -Waddress"
                        extraopts="${extraopts} -Wswitch-default -Wswitch-enum -Wunused-parameter"
                        extraopts="${extraopts} -Wfloat-equal -Wshadow -Wconversion -Wwrite-strings"
                        extraopts="${extraopts} -Wmissing-field-initializers -Wpadded -Wredundant-decls"
                        extraopts="${extraopts} -Wunreachable-code -Wvolatile-register-var -Wctor-dtor-privacy"
                        extraopts="${extraopts} -Wnon-virtual-dtor -Wsign-promo -Wreorder -Wno-pmf-conversions"
                        ;;
                    *) echo "Unknown compiler option $2"; usage ;;
                esac
                shift
                ;;

            #*) echo "Unknown argument: $1"; usage ;;
        esac
        shift
    done
    
    if [ "${source}" = "" ]; then
        islib=1;
    fi
}

######## END FUNCTIONS ########

if [ $useuni -eq 1 ]; then
    defines="${defines} -D_UNICODE -DUNICODE"
fi

parse_args "$@"
extraopts="${fexcep} ${extraopts}"

if [ $nopthread -eq 0 ]; then
    extraopts="${extraopts} -pthread"
fi

if [ $no_console -eq 0 ]; then
    defines="${defines} -D_CONSOLE"
fi

if [ $has_debug -eq 0 ]; then
    defines="${defines} -DNDEBUG"
fi

binfldr="${odir}/bin"
objdir="${odir}/obj"
asmdir="${odir}/asm"
utofile="${binfldr}/omni.a"

if [ ! -d ${objdir} ]; then
    msg "mkdir ${objdir}"
    mkdir ${objdir}
    msg "chmod 777 ${objdir}"
    chmod 777 ${objdir}
fi
if [ ! -d ${asmdir} ]; then
    msg "mkdir ${asmdir}"
    mkdir ${asmdir}
    msg "chmod 777 ${asmdir}"
    chmod 777 ${asmdir}
fi

if [ $docleanup -eq 1 ]; then
	msg ""
	msg "Removing old files"
    msg ""
    
    if [ -f ${utofile} ]; then
        msgp 1 "rm -f ${utofile}"
	fi
	if [ -f ${prog} ]; then
        msgp 1 "rm -f ${prog}"
	fi
	if [ -f ${err_log_file} ]; then
        if [ "$err_log_file" != "" ]; then
            msgp 1 "rm -f ${err_log_file}"
        fi
	fi
	if [ -f ${log_file} ]; then
        if [ "$log_file" != "" ]; then
            msgp 1 "rm -f ${log_file}"
        fi
	fi
    if [ -d ${objdir} ]; then
        msgp 1 "rm -f ${objdir}/*.o"
    fi
    if [ -d ${asmdir} ]; then
        msgp 1 "rm -f ${asmdir}/*.s"
    fi
fi

unm=`uname -a`
if [ "$log_file" != "" ]; then echo "System: ${unm}" >> ${log_file}; fi
if [ "$err_log_file" != "" ]; then echo "System: ${unm}" >> ${err_log_file}; fi

pdnm=`dirname ${prog}`
if [ ! -d ${pdnm} ]; then
    msg "${pdnm} does not exist, creating..."
    mkdir -p ${pdnm}
    if [ ! -d ${pdnm} ]; then
        msg "SCRIPT ERROR: could not create ${pdnm}, bailing..."
        exit 0
    fi
fi

if [ $verbose -gt 2 ]; then
	msg "---Settings---"
	msg "Toolchain: ${toolchain}"
    if [ $islib -eq 1 ]; then
        msg "Libchain: ${libchain}"
        msg "Libops: ${libops}"
    fi
	msg "Prog name: ${prog}"
	msg "Defines: ${defines}"
	msg "Includes: ${includes}"
	msg "Extra options: ${extraopts}"
	msg ""
	msg "---Source Files---"
	msg "${source}"
    msg ""
fi

if [ $islib -eq 0 ]; then
    source="${source} ${fwsrc}"
else
    curdate=`date "+%Y-%m-%d %H:%M:%S"`
    msg "${curdate}: Compiling Omni object files ..."
    #src_files=$(echo $source | tr ' ' '\n')
    src_files=$(echo $fwsrc)
    ofiles=
    for srcfile in $src_files; do
        ofile=$(basename "$srcfile")
        exten="${ofile##*.}"
        sfile="${asmdir}/${ofile%.*}.s"
        ofile="${objdir}/${ofile%.*}.o"
        ofiles="${ofiles} ${ofile}"
        ccout="$toolchain $srcfile -o$ofile $defines $includes -c $extraopts"
        scout="$toolchain $srcfile -o$sfile $defines $includes -S $extraopts"
        if [ "$log_file" != "" ]; then
            ccout="${ccout} >> ${log_file}"
            scout="${scout} >> ${log_file}"
        fi
        if [ "$err_log_file" != "" ]; then
            ccout="${ccout} 2>> ${err_log_file}"
            scout="${scout} 2>> ${err_log_file}"
        fi
        if [ $verbose -gt 2 ]; then
            logout=${ccout}
        else
            logout=${srcfile##/*/}
        fi
        msg "${logout}"
        if [ $parse_only -eq 0 ]; then
            if [ $doasm -eq 1 ]; then
                eval $scout
            fi
            eval $ccout
        fi
    done
    if [ $syntax_only -eq 0 ]; then
        msg ""
        curdate=`date "+%Y-%m-%d %H:%M:%S"`
        msg "${curdate}: Linking object files into library ..."
        lnout="$libchain $libops $utofile $ofiles"
        if [ "$log_file" != "" ]; then lnout="${lnout} >> ${log_file}"; fi
        if [ "$err_log_file" != "" ]; then lnout="${lnout} 2>> ${err_log_file}"; fi
        msgp 1 "${lnout}"
        msg ""
        if [ $parse_only -eq 0 ]; then
            curdate=`date "+%Y-%m-%d %H:%M:%S"`
            msg "${curdate}: Build status for ${utofile}"
            if [ -f ${utofile} ]; then
                msg "SUCCESS"
            else
                msg "FAIL"
            fi
        fi
    fi
fi
msg ""
if [ "${source}" != "" ]; then
    curdate=`date "+%Y-%m-%d %H:%M:%S"`
    msg "${curdate}: Compiling program source ..."
    src_files=$(echo $source)
    ofiles=
    for srcfile in $src_files; do
        ofile=$(basename "$srcfile")
        exten="${ofile##*.}"
        sfile="${asmdir}/${ofile%.*}.s"
        ofile="${objdir}/${ofile%.*}.o"
        ofiles="${ofiles} ${ofile}"
        ccout="$toolchain $srcfile -o$ofile $defines $includes -c $extraopts"
        scout="$toolchain $srcfile -o$sfile $defines $includes -S $extraopts"
        if [ "$log_file" != "" ]; then
            ccout="${ccout} >> ${log_file}"
            scout="${scout} >> ${log_file}"
        fi
        if [ "$err_log_file" != "" ]; then
            ccout="${ccout} 2>> ${err_log_file}"
            scout="${scout} 2>> ${err_log_file}"
        fi
        if [ $verbose -gt 2 ]; then
            logout=${ccout}
        else
            logout=${srcfile##/*/}
        fi
        msg "${logout}"
        if [ $parse_only -eq 0 ]; then
            if [ $doasm -eq 1 ]; then
                eval $scout
            fi
            eval $ccout
        fi
    done
    
    if [ $syntax_only -eq 0 ]; then
        #link here
        msg ""
        curdate=`date "+%Y-%m-%d %H:%M:%S"`
        libfile=
        if [ $islib -eq 1 ]; then
            libfile=${utofile}
        fi
        msg "${curdate}: Linking program object files ..."
        lnout="$toolchain $ofiles $libfile -o $prog $defines $includes $extraopts"
        if [ "$log_file" != "" ]; then lnout="${lnout} >> ${log_file}"; fi
        if [ "$err_log_file" != "" ]; then lnout="${lnout} 2>> ${err_log_file}"; fi
        msgp 1 "${lnout}"
        msg ""
        if [ $parse_only -eq 0 ]; then
            curdate=`date "+%Y-%m-%d %H:%M:%S"`
            msg "${curdate}: Build status for ${prog}"
            if [ -f ${prog} ]; then
                msg "SUCCESS"
            else
                msg "FAIL"
            fi
        fi
    else
        msg ""
        msg "Syntax check complete"
    fi
fi
    
msg ""
