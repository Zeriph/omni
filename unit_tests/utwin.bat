@echo off
setlocal enabledelayedexpansion

REM set extralibs="WS2_32.lib" "Mswsock.lib" "AdvAPI32.lib" "User32.lib"
set omni_lib_loc=G:

set hodir=0
for %%a in (%*) do (
    if !hodir! equ 1 (
        set omni_lib_loc=%%a
        set hodir=0
    )
    if "%%a"=="-odir" (
        set hodir=1
    )
)

set binfldr=%omni_lib_loc%\unit_tests\bin
set utloc=%omni_lib_loc%\unit_tests\units
set unit_tests=
for %%u in (!utloc!\*.hpp) do (
    set tname=%%u
    call set tname=%%tname:!utloc!\=%%
    call set tname=%%tname:.hpp=%%
    set unit_tests=!unit_tests! !tname!
)

set utest=all
set tmput=all
set utestflag=
set use_log=0
set eopts=
set edefs=
set libs=
set vs=
set llog=
set wasEr=0
set pwd=%cd%
set uvar=-u
set noopt=0
set extralibs=
set sys_type=win

:argloop
if not "%1"=="" (
    REM compile script options
	if "%1"=="-c" (
		set eopts=%eopts% -c %2
		set useeo=1
		shift
    ) else if "%1"=="-d" (
        set edefs=%edefs% -d %2
        shift
    ) else if "%1"=="-l" (
		set libs=%libs% -l %2
        shift
    ) else if "%1"=="-log" (
		set use_log=1
    ) else if "%1"=="-single" (
        set eopts=%eopts% -single
    ) else if "%1"=="-lib" (
        set eopts=%eopts% -lib
    ) else if "%1"=="-v" (
		set vs=-v
	) else if "%1"=="-vv" (
		set vs=-vv
	) else if "%1"=="-vvv" (
		set vs=-vvv
	) else if "%1"=="-v2" (
		set vs=-vv
	) else if "%1"=="-v3" (
		set vs=-vvv
    ) else if "%1"=="-po" (
		set eopts=%eopts% -po
	) else if "%1"=="-?" (
		goto showusage
    ) else if "%1"=="-list" (
        goto list_tests
    REM framework options
    ) else if "%1"=="-stdcall" (
        set eopts=%eopts% -oo stdcall
    ) else if "%2"=="-fastcall" (
        set eopts=%eopts% -oo fastcall
    ) else if "%2"=="-cdecl" (
        set eopts=%eopts% -oo cdecl
    REM framework debug options
    ) else if "%1"=="-d1" (
        set eopts=%eopts% -dbg 1
    ) else if "%1"=="-d2" (
        set eopts=%eopts% -dbg 2
    ) else if "%1"=="-d3" (
        set eopts=%eopts% -dbg 3
    ) else if "%1"=="-d4" (
        set eopts=%eopts% -dbg 4
    ) else if "%1"=="-d5" (
        set eopts=%eopts% -dbg 5
    ) else if "%1"=="-derr" (
        set eopts=%eopts% -dbg err
    ) else if "%1"=="-dfl" (
        set eopts=%eopts% -dbg file
    ) else if "%1"=="-dfn" (
        set eopts=%eopts% -dbg func
    ) else if "%1"=="-dln" (
        set eopts=%eopts% -dbg line
    ) else if "%1"=="-dbg1" (
        set eopts=%eopts% -dbg 1 -dbg file -dbg func -dbg line
    ) else if "%1"=="-dbg2" (
        set eopts=%eopts% -dbg 2 -dbg file -dbg func -dbg line
    ) else if "%1"=="-dbg3" (
        set eopts=%eopts% -dbg 3 -dbg file -dbg func -dbg line
    ) else if "%1"=="-dbg4" (
        set eopts=%eopts% -dbg 4 -dbg file -dbg func -dbg line
    ) else if "%1"=="-dbg5" (
        set eopts=%eopts% -dbg 5 -dbg file -dbg func -dbg line
	REM compiler/linker options
    ) else if "%1"=="-np" (
		set eopts=%eopts% -co np
	) else if "%1"=="-x86" (
		set eopts=%eopts% -co x86
	) else if "%1"=="-x64" (
		set eopts=%eopts% -co x64
	) else if "%1"=="-effc" (
		set eopts=%eopts% -co effc
	) else if "%1"=="-we" (
		set eopts=%eopts% -co we
	) else if "%1"=="-se" (
		set eopts=%eopts% -co se
    ) else if "%1"=="-nortti" (
        set eopts=%eopts% -co nortti
    ) else if "%1"=="-opti" (    
        set eopts=%eopts% -co opti
    ) else if "%1"=="-opt1" (
        set eopts=%eopts% -co opt2
    ) else if "%1"=="-opt2" (
        set eopts=%eopts% -co opt2
    ) else if "%1"=="-opt3" (
        set eopts=%eopts% -co opt3
    ) else if "%1"=="-opts" (
        set eopts=%eopts% -co opts
    ) else if "%1"=="-noopt" (
        set noopt=1
    ) else if "%1"=="-asm" (
        set eopts=%eopts% -co asm
    ) else if "%1"=="-gdb" (
        set eopts=%eopts% -co gdb
        set uvar=
    ) else if "%1"=="-syntax" (
        set eopts=%eopts% -co syntax
    ) else if "%1"=="-eo" (
		set eopts=%eopts% -co xtra
    ) else if "%1"=="-vs2005" (
		set eopts=%eopts% -co vs2005
	) else if "%1"=="-vs2008" (
		set eopts=%eopts% -co vs2008
	) else if "%1"=="-vs2010" (
		set eopts=%eopts% -co vs2010
	) else if "%1"=="-vs2012" (
		set eopts=%eopts% -co vs2012
    ) else if "%1"=="-vs2013" (
		set eopts=%eopts% -co vs2013
    ) else if "%1"=="-vs2015" (
		set eopts=%eopts% -co vs2015
    ) else if "%1"=="-vs2017" (
		set eopts=%eopts% -co vs2017
    ) else if "%1"=="-odir" (
        shift
	) else (
        set tmput=%1
	)
	shift
	goto argloop
)

call :parse_test %tmput% wasEr
if !wasEr! equ 1 (
    echo Unknown argument: %1
    call :showusage
)

if %use_log% equ 1 (
	set llog=-log "%omni_lib_loc%\build\logs\!sys_type!_build.log"
)
if %noopt% equ 0 (
    set eopts=%eopts% -co opti -co opt3 -co opts
)

set utcpp=main.cpp
set utofile=!binfldr!\!sys_type!_test.exe
set utdef=-s !omni_lib_loc!\unit_tests\!utcpp! -i !omni_lib_loc!\unit_tests -d !utestflag!

set cpopt=call compile.bat %utdef% %uvar% -o %utofile% %eopts% %edefs% %vs% %llog% %libs%
echo %cpopt%
%cpopt%

REM delete the program database files
REM @del %pwd%\bin\*.ilk
REM @del %pwd%\bin\*.pdb

goto eeof

:showusage
echo usage: utwin [test] [flags]
echo.
echo FLAGS:
echo  Valid falgs that can be passed to the compile script are as follows:
echo.
echo compile script options:
echo        -?           Display this help
echo        -c [opts]    Pass extra arguments to the compiler
echo        -d [define]  Pass extra defines to the compiler
echo        -l           Use extra libs (%extralibs%)
echo        -v           This flag signifies the verbosity level of the compiler
echo                     output. Valid '-v' values are as follows:
echo                     -v          = Verbose level 1 (basic output)
echo                     -vv/-v2     = Verbose L2 (show more output)
echo                     -vvv/-v3    = Verbose L3 (show ALL output)
echo        -single      Builds library.cpp
echo        -lib         Builds omni.liv then links against it for the unit tests
echo        -log         Log the output to the logs folder
echo        -po          Parse the compile script only
echo.
echo framework options:
echo        -stdcall    Defines the calling convention to be of stdcall
echo        -fastcall   Defines the calling convention to be of fastcall
echo        -cdecl      Defines the calling convention to be of cdecl
echo.
echo framework debug options:
echo        -d1         Sets the OMNI_SHOW_DEBUG=1
echo        -d2         Sets the OMNI_SHOW_DEBUG=2
echo        -d3         Sets the OMNI_SHOW_DEBUG=3
echo        -d4         Sets the OMNI_SHOW_DEBUG=4
echo        -d5         Sets the OMNI_SHOW_DEBUG=5
echo        -derr       Sets OMNI_SHOW_DEBUG_ERR
echo        -dfl        Sets OMNI_SHOW_DEBUG_FILE
echo        -dfn        Sets OMNI_SHOW_DEBUG_FUNC
echo        -dln        Sets OMNI_SHOW_DEBUG_LINE
echo        -dbgX       equivilant to -dX -dfl -dfn -dln
echo.
echo compiler options:
echo        -x86        Enable 32-bit compilation
echo        -x64        Enable 64-bit compilation
echo        -eo         Use the extra compiler/linker flags (can generate erroneous errors)
echo        -we         Treat all warnings as errors
echo        -nortti     Disables RTTI (run-time type information) for C++
echo        -noopt      No optimizations (default of -opti -opt3 -opts)
echo        -opti       Enable global optimization with intrinsic functions (/Oi /Og)
echo        -opt1       Enable optimizations (/O1)
echo        -opt2       Enable more optimizations (/O2)
echo        -opt3       Maximum optimizations (/Ox)
echo        -opts       Favor code space (/Os)
echo        -asm        Generate the assembly output (/FAs, .asm file name)
echo        -gdb        Sets the -ggdb flag, enabling GDB debug output
echo        -syntax     Sets the -fsyntax-only flag which checks the code for syntax
echo                    errors only and does nothing beyond that
echo        -vs2005     Specifies to use Visual Studio 2005 (v8.0) and WinSDK 6
echo        -vs2008     Specifies to use Visual Studio 2008 (v9.0) and WinSDK 7
echo        -vs2010     Specifies to use Visual Studio 2010 (v10.0) and WinSDK 7.1
echo        -vs2012     Specifies to use Visual Studio 2012 (v11.0) and WinSDK 8.0
echo        -vs2013     Specifies to use Visual Studio 2013 (v12.0) and WinSDK 8.1
echo        -vs2015     Specifies to use Visual Studio 2015 (v14.0) and WinSDK 10.0.15063.0
echo        -vs2017     Specifies to use Visual Studio 2017 (v15.0) and WinSDK 10.0.16299.0
echo.
goto eeof

:list_test
echo Current tests available:
for %%t in (%unit_tests%) do (
    echo - %%t
)
goto eeof

:parse_test
set ut=
for %%t in (%unit_tests%) do (
    if "%1"=="%%t" (
        set ut=%1
        goto :end_prase_loop
    )
)
:end_prase_loop

if "%ut%"=="" (
    echo Invalid unit test specified: %ut%
    set %2=1
) else (    
    set utest=%ut%
    set utupper=
    call :toupper !utest! utupper
    set utestflag=OMNI_UT_!utupper!
    if "%ut%"=="full" (
        set eopts=!eopts! -d _UNICODE -d UNICODE -d OMNI_NON_PORTABLE
        set eopts=!eopts! -d OMNI_DISPOSE_EVENT -d OMNI_OBJECT_NAME -d OMNI_TYPE_INFO
        set eopts=!eopts! -d OMNI_SAFE_FRAMEWORK -d OMNI_COMPILE_FLAGS
        set eopts=!eopts! -d _CONSOLE -d NDEBUG
    ) else if "%ut%"=="all" (
        set eopts=!eopts! -d OMNI_COMPILE_FLAGS
    )
)
goto :eof

:toupper
REM call :toupper string_to_conver string_to_store
set ucase=A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
set uctmp=%1
set ulist=%ucase%
for %%Z in (%ucase%) do set uctmp=!uctmp:%%Z=%%Z!
set %2=%uctmp%
goto :eof

:eeof
endlocal
goto :eof
