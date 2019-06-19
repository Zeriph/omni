#!/bin/sh
omni_src_dir=/source/omni
pdir=`pwd`
objdir=${pdir}/obj
outdir=${pdir}/output
libname=${outdir}/omni.a
src=

# set source, only setting it this way so it's easier to
# read on screen (and it's easy to # out a source we don't want)
<zeriph_inline_source>src="${src} ${omni_src_dir}/{0.nm_path}"</zeriph_inline_source>

if [ ! -d ${objdir} ]; then
    echo "mkdir ${objdir}"
    mkdir ${objdir}
fi
if [ ! -d ${outdir} ]; then
    echo "mkdir ${outdir}"
    mkdir ${outdir}
fi

# loop through and compile source to object files for linking
src_files=$(echo $src | tr " " "\n")
ofiles=
for srcfile in $src_files; do
    ofile="${objdir}${srcfile#*${omni_src_dir}}.o"
	ofiles="${ofiles} ${ofile}"
    echo "g++ $srcfile -o$ofile -I$omni_src_dir -c -pthread -rt -03 -DNDEBUG -D_CONSOLE -fexecptions -D_UNICODE -DUNICODE"
    g++ $srcfile -o$ofile -I$omni_src_dir -c -pthread -rt -03 -DNDEBUG -D_CONSOLE -fexecptions -D_UNICODE -DUNICODE
done

# create static lib
echo "ar rvs $libname $ofiles"
ar rvs $libname $ofiles

