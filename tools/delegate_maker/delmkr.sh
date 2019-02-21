#!/bin/sh

# PNUMPT1
# PNUMPTF1

base=`dirname 0`
if [ "$base" == "." ]; then
    base=`pwd`
fi

lfile="license.txt"
tfile="${base}/template.hpp"
outdir="${base}"
cnt=16
verbose=0
pnumptf=
pnumpt=
pnumtdef=
pnumtdoxdef=
pnumdata=
pnumdataval=
pnumdatavalvar=
pnumvals=
nl=$'\n'

vout()
{
    if [ $verbose -ge 1 ]; then
        echo $1
    fi
}

vvout()
{
    if [ $verbose -ge 2 ]; then
        echo $1
    fi
}

usage()
{
    echo "usage: delmkr.sh [-f INPUT] [-d OUTDIR] [-n NUM] [-l LFILE] [-v]"
    echo 
    echo "FLAGS:"
    echo "   -f INPUT       Specifies an input file"
    echo "                  default: $tfile"
    echo "   -d OUTDIR      Specifies the output directory for the headers"
    echo "                  default: $outdir"
    echo "   -n NUM         The max number of delegates you wish to create"
    echo "                  default: $cnt"
    echo "   -l LFILE       Specifies the license file to use for delegates.hpp"
    echo "                  default: $lfile"
    echo "   -v             Shows verbose output"
    exit 1
}

makehpp()
{
    echo "Generating ${outdir}/delegates.hpp"
    cat ${lfile} > "${outdir}/delegates.hpp"
    
    tnum=0
    printf "\n%s\n" "#if !defined(OMNI_DELEGATES_HPP)" >> "${outdir}/delegates.hpp"
    echo "#define OMNI_DELEGATES_HPP 1" >> "${outdir}/delegates.hpp"
    echo "" >> "${outdir}/delegates.hpp"
    while [ $tnum -lt $cnt ]; do
        echo "#include <omni/delegate/${tnum}.hpp>" >> "${outdir}/delegates.hpp"
        tnum=$((tnum+1))
    done
    echo "" >> "${outdir}/delegates.hpp"
    echo "// DEV_NOTE: this is here for MS compilers and how they expand macro variables and the __VA_ARGS__" >> "${outdir}/delegates.hpp"
    echo "#define OMNI_EXPAND_FW(x) x" >> "${outdir}/delegates.hpp"
    
    echo "" >> "${outdir}/delegates.hpp"
    tnum=0
    printf "%s" "#define OMNI_DELEGATE_GET_MACRO_FW(" >> "${outdir}/delegates.hpp"
    while [ $tnum -lt $cnt ]; do
        printf "_%d," ${tnum} >> "${outdir}/delegates.hpp"
        tnum=$((tnum+1))
    done
    echo "NAME,...) OMNI_EXPAND_FW( NAME )" >> "${outdir}/delegates.hpp"
    
    echo "" >> "${outdir}/delegates.hpp"
    tnum=$((cnt-1))
    printf "%s" "#define OMNI_EVENT_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_MACRO_FW(__VA_ARGS__" >> "${outdir}/delegates.hpp"
    while [ $tnum -gt 0 ]; do
        printf ", OMNI_EVT%d_FW" ${tnum} >> "${outdir}/delegates.hpp"
        tnum=$((tnum-1))
    done
    echo ", OMNI_EVT0_FW) )OMNI_EXPAND_FW( (__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    tnum=$((cnt-1))
    printf "%s" "#define OMNI_DELEGATE_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_MACRO_FW(__VA_ARGS__" >> "${outdir}/delegates.hpp"
    while [ $tnum -gt 0 ]; do
        printf ", OMNI_DEL%d_FW" ${tnum} >> "${outdir}/delegates.hpp"
        tnum=$((tnum-1))
    done
    echo ", OMNI_DEL0_FW) )OMNI_EXPAND_FW( (__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    
    echo "" >> "${outdir}/delegates.hpp"
    tnum=0
    printf "#define OMNI_DELEGATE_GET_BIND_MACRO_FW(" >> "${outdir}/delegates.hpp"
    while [ $tnum -lt $cnt ]; do
        printf "_%d," ${tnum} >> "${outdir}/delegates.hpp"
        tnum=$((tnum+1))
    done
    echo "Class,Function,Obj,NAME,...) OMNI_EXPAND_FW( NAME )" >> "${outdir}/delegates.hpp"
    tnum=$((cnt-1))
    printf "%s" "#define OMNI_DELEGATE_BIND_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_BIND_MACRO_FW(__VA_ARGS__" >> "${outdir}/delegates.hpp"
    while [ $tnum -gt 0 ]; do
        printf ", OMNI_BIND%d" ${tnum} >> "${outdir}/delegates.hpp"
        tnum=$((tnum-1))
    done
    echo ", OMNI_BIND0) )OMNI_EXPAND_FW( (__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    tnum=$((cnt-1))
    printf "%s" "#define OMNI_DELEGATE_BIND_CONST_DEF_FW(...) OMNI_EXPAND_FW( OMNI_DELEGATE_GET_BIND_MACRO_FW(__VA_ARGS__" >> "${outdir}/delegates.hpp"
    while [ $tnum -gt 0 ]; do
        printf ", OMNI_BIND%d_CONST" ${tnum} >> "${outdir}/delegates.hpp"
        tnum=$((tnum-1))
    done
    echo ", OMNI_BIND0_CONST) )OMNI_EXPAND_FW( (__VA_ARGS__) )" >> "${outdir}/delegates.hpp"

    echo "" >> "${outdir}/delegates.hpp"
    echo "#define OMNI_EVENT(...) OMNI_EXPAND_FW( OMNI_EVENT_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "#define omni_event(...) OMNI_EXPAND_FW( OMNI_EVENT_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "" >> "${outdir}/delegates.hpp"
    echo "#define OMNI_DELEGATE(...) OMNI_EXPAND_FW( OMNI_DELEGATE_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "#define omni_delegate(...) OMNI_EXPAND_FW( OMNI_DELEGATE_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "" >> "${outdir}/delegates.hpp"
    echo "#define OMNI_BIND(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "#define omni_bind(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "" >> "${outdir}/delegates.hpp"
    echo "#define OMNI_BIND_CONST(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_CONST_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "#define omni_bind_const(...) OMNI_EXPAND_FW( OMNI_DELEGATE_BIND_CONST_DEF_FW(__VA_ARGS__) )" >> "${outdir}/delegates.hpp"
    echo "" >> "${outdir}/delegates.hpp"
    echo "#endif // OMNI_DELEGATES_HPP" >> "${outdir}/delegates.hpp"
    #echo "" >> "${outdir}/delegates.hpp"
}

while [ "$*" != "" ]; do
    case $1 in
        "-f") tfile="$2" ; shift ;;
        "-d") outdir="$2"; shift ;;
        "-n") cnt=$2; shift ;;
        "-l") lfile="$2"; shift ;;
        "-v") verbose=$((verbose+1)) ;;
        *) usage ;;
    esac
    shift
done

outdir="${outdir}"

vout "Input file: ${tfile}"
vout "Output directory: ${outdir}"
vout "Max template argument count: ${cnt}"

if [ ! -d ${outdir} ]; then
    res="n"
    echo -ne "Directory ${outdir} does not exist, create [y/n]? "
    read res
    if [ "$res" == "y" ] || [ "$res" == "Y" ]; then
        mkdir ${outdir}
    fi
fi
if [ -d ${outdir} ]; then
    if [ $cnt -lt 1 ]; then
        cnt=1
    fi
    num=1
    cnt=$((cnt+1))
    while [ $num -lt $cnt ]; do
        ofile="${outdir}/delegate/${num}.hpp"
        vout "Parsing header ${ofile}"
        tnum=1
        ptX=
        ptX1=
        ptX_t=
        pnumptf1=
        pnumpt1=
        pnumptf=
        pnumpt=
        pnumtdef=
        pnumtdoxdef=
        pnumdata=
        pnumdataval=
        pnumdatavalvar=
        pnumvals=
        while [ $tnum -le $num ]; do
            ptX="PT${tnum}"
            ptX1="PT1_${tnum}"
            ptX_t="p${tnum}_t"
            pnumptf1="${pnumptf1}${ptX1}"
            pnumpt1="${pnumpt1}typename ${ptX1}"
            pnumptf="${pnumptf}${ptX}"
            pnumpt="${pnumpt}typename ${ptX}"
            if [ $tnum -lt 4 ]; then
                if [ $tnum -eq 1 ]; then
                    pnumtdoxdef="${pnumtdoxdef}\ \ \ \ \ \*\ \@tparam ${ptX}\ \ \ \ \ Specifies the 1st parameter type passed to the function delegateDELMKR_NL"
                    pnumtdef="${pnumtdef}\ \ \ \ \ \ \ \ \ \ \ \ \/\*\* Defines the 1st function parameter type of this delegate \*\/DELMKR_NL"
                elif [ $tnum -eq 2 ]; then
                    pnumtdoxdef="${pnumtdoxdef}\ \ \ \ \ \*\ \@tparam ${ptX}\ \ \ \ \ Specifies the 2nd parameter type passed to the function delegateDELMKR_NL"
                    pnumtdef="${pnumtdef}\ \ \ \ \ \ \ \ \ \ \ \ \/\*\* Defines the 2nd function parameter type of this delegate \*\/DELMKR_NL"
                elif [ $tnum -eq 3 ]; then
                    pnumtdoxdef="${pnumtdoxdef}\ \ \ \ \ \*\ \@tparam ${ptX}\ \ \ \ \ Specifies the 3rd parameter type passed to the function delegateDELMKR_NL"
                    pnumtdef="${pnumtdef}\ \ \ \ \ \ \ \ \ \ \ \ \/\*\* Defines the 3rd function parameter type of this delegate \*\/DELMKR_NL"
                fi
                pnumtdef="${pnumtdef}\ \ \ \ \ \ \ \ \ \ \ \ typedef ${ptX} ${ptX_t};DELMKR_NL"
            else
                pnumtdoxdef="${pnumtdoxdef}\ \ \ \ \ \*\ \@tparam ${ptX}\ \ \ \ \ Specifies the ${tnum}th parameter type passed to the function delegateDELMKR_NL"
                pnumtdef="${pnumtdef}\ \ \ \ \ \ \ \ \ \ \ \ \/\*\* Defines the ${tnum}th function parameter type of this delegate \*\/DELMKR_NL"
                pnumtdef="${pnumtdef}\ \ \ \ \ \ \ \ \ \ \ \ typedef ${ptX} ${ptX_t};DELMKR_NL"
            fi
            pnumdata="${pnumdata}${ptX_t}"
            pnumdataval="${pnumdataval}${ptX_t} val${tnum}"
            pnumdatavalvar="${pnumdatavalvar}val${tnum}"
            pnumvals="${pnumvals}void*"
            if [ $tnum -le $((num-1)) ]; then
                pnumptf1="${pnumptf1}, "
                pnumpt1="${pnumpt1}, "
                pnumptf="${pnumptf}, "
                pnumpt="${pnumpt}, "
                pnumdata="${pnumdata}, "
                pnumdataval="${pnumdataval}, "
                pnumdatavalvar="${pnumdatavalvar}, "
                pnumvals="${pnumvals}, "
            fi
            tnum=$((tnum+1))
        done
        sedpnumvals="sed -e 's/PNUMVALS/${pnumvals}/g'"
        sedpnumptf1="sed -e 's/PNUMPTF1/${pnumptf1}/g'"
        sedpnumpt1="sed -e 's/PNUMPT1/${pnumpt1}/g'"
        sedpnumptf="sed -e 's/PNUMPTF/${pnumptf}/g'"
        sedpnumpt="sed -e 's/PNUMPT/${pnumpt}/g'"
        sedpnumdatavalvar="sed -e 's/PNUMDATAVALVAR/${pnumdatavalvar}/g'"
        sedpnumdataval="sed -e 's/PNUMDATAVAL/${pnumdataval}/g'"
        sedpnumdata="sed -e 's/PNUMDATA/${pnumdata}/g'"
        sedpnumtdef="sed -e 's/PNUMTDEF/${pnumtdef}/g'"
        sedpnumtdoxdef="sed -e 's/PNUMTDOXDEF/${pnumtdoxdef}/g'"
        sednum="sed -e 's/PNUM/${num}/g'"
        exe="cat ${tfile} | ${sedpnumvals} | ${sedpnumpt1} | ${sedpnumptf1} | ${sedpnumptf} | ${sedpnumpt} | ${sedpnumdatavalvar} | ${sedpnumdataval} | ${sedpnumdata} | ${sedpnumtdef} | ${sedpnumtdoxdef} | ${sednum}  > ${ofile}.tmp"
        vvout "${exe}"
        eval ${exe}
        
        sed 's/DELMKR_NL/\
/g' "${ofile}.tmp" > "${ofile}"
        rm -f "${ofile}.tmp"
        
        if [ -f ${ofile} ]; then        
            echo "Generated: ${ofile}"
        else
            echo "Did not generate output file ${ofile}"
        fi
        num=$((num+1))
    done
    makehpp
else
    echo "Directory ${outdir} does not exist"
fi
