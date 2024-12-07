@echo off
setlocal enabledelayedexpansion
REM to use a differnt Visual Studio, change the VSDIR and VSLIB variables appropriatly
REM to change to 64 bit, switch to the 64 bit bin/lib, and change MACH_T=/MACHINE:X64
set VSDIR="C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin"
set VSLIB="C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib"
set OMNI_SRC_DIR=C:\source\omni
set PROJECTDIR=%CD%
set OBJDIR=%PROJECTDIR%\obj\
set OUTDIR=%PROJECTDIR%\output
set LIBNAME=%OUTDIR%\omni.lib
set MACH_T=/MACHINE:X86
set SOURCE=

REM set source, only setting it this way so it's easier to
REM read on screen (and it's easy to REM out a source we don't want)
<zeriph_inline_source>\set SOURCE=%SOURCE% %OMNI_SRC_DIR%\{0.nm_path}</zeriph_inline_source>

REM create the directories if they don't exist
if not exist %OBJDIR% (
	echo mkdir %OBJDIR%
	mkdir %OBJDIR%
)
if not exist %OUTDIR% (
    echo mkdir %OUTDIR%
    mkdir %OUTDIR%
)

REM loop through source and compile into object files for linking
set lnklist=
for %%s in (%SOURCE%) do (
	set srcname=%%s
	set srcf=!srcname!
	set srcname=%cd%\obj\%%~ns.obj
    REM set the list of files to link against (the .obj files)
	set lnklist=!lnklist! !srcname!
    echo %VSDIR%\cl.exe /c %%s /Fo!srcname! /I%OMNI_SRC_DIR% /TP /MD /EHsc /nologo /03 /DNDEBUG /D_CONSOLE /D_UNICODE /DUNICODE
	%VSDIR%\cl.exe /c %%s /Fo!srcname! /I%OMNI_SRC_DIR% /TP /MD /EHsc /nologo /03 /DNDEBUG /D_CONSOLE /D_UNICODE /DUNICODE
)

REM create static lib
echo %VSDIR%\lib.exe !lnklist! /OUT:%LIBNAME% /LIBPATH:%VSLIB% %MACH_T%
%VSDIR%\lib.exe !lnklist! /OUT:%LIBNAME% /LIBPATH:%VSLIB% %MACH_T%

:eof
endlocal