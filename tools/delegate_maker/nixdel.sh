#!/bin/sh

odir="/Code/omni"
#u=jink
#g=staff

parse_args()
{
    while [ "$*" != "" ]; do
		case $1 in
			"-o") odir="$2"; shift ;;
        esac
		shift
	done
}

parse_args $*

if [ ! -d "${odir}" ]; then
    echo "Folder not found: ${odir}"
    exit 1
fi

sodir="${odir}/source/omni"
base="${odir}/tools/delegate_maker"
tfile="${base}/template.hpp"
lfile="${odir}/docugen/doc_license.txt"

dlmkr="sh ${base}/delmkr.sh -f ${tfile} -d ${sodir} -n 16 -l ${lfile}"
#dlown="chown -R ${u} ${sodir}/delegate* && chgrp -R ${g} ${sodir}/delegate*"
#dlmod="chmod -R 755 ${sodir}"

echo ${dlmkr}
eval ${dlmkr}

#echo ${dlown}
#eval ${dlown}

echo ${dlmod}
eval ${dlmod}
