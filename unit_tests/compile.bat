@echo off
setlocal enabledelayedexpansion
REM note: setlocal is needed for this build script to parse properly

REM set extraopts=/Gd /Ox /Oi /Ot /MT /nologo /TP !fexcep! !extraopts!
REM set defines=/D _WIN32 /D "NDEBUG" /D "_CONSOLE"
REM set libs="WSock32.lib"
REM set libops="rvs"
REM set defines=%defines% /D "_UNICODE" /D "UNICODE"

REM "%vsfldr%\bin\cl.exe"
REM /MACHINE:X86 /LIBPATH:vsfldr%\LIB" /LIBPATH:"%vsfldr%\atlmfc\lib" /LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.0\Lib"
REM -OPTIMIZATION-
REM /Od disable optimizations (default)         /Og enable global optimization
REM /Oi[-] enable intrinsic functions           /Ob<n> inline expansion (default n=0)
REM /Os favor code space                        /Ot favor code speed
REM /O1 minimize space                          /O2 maximize speed
REM /Ox maximum optimizations
REM /favor:<blend|AMD64|INTEL64> select processor to optimize for, one of:
REM     blend - a combination of optimizations for several different x64 processors
REM     AMD64 - 64-bit AMD processors
REM     INTEL64 - Intel(R)64 architecture processors
REM -CODE GENERATION-
REM /GF enable read-only string pooling         /Gy[-] separate functions for linker
REM /Gm[-] enable minimal rebuild               /GS[-] enable security checks
REM /GR[-] enable C++ RTTI                      /GX[-] enable C++ EH (same as /EHsc)
REM /EHs enable C++ EH (no SEH exceptions)      /EHa enable C++ EH (w/ SEH exceptions)
REM /EHc extern "C" defaults to nothrow
REM When compiling with /EHs, a catch(...) block will not catch a structured exception (divide by zero, null pointer, for example);
REM a catch(...) block will only catch explicitly-thrown, C++ exceptions. 
REM /Gd __cdecl calling convention              /Gr __fastcall calling convention
REM /Gz __stdcall calling convention            /GZ Enable stack checks (/RTCs)
REM /GL[-] enable link-time code generation     /GA optimize for Windows Application
REM /Ge force stack checking for all funcs      /GZ Enable stack checks (/RTCs)
REM /RTCs Stack Frame runtime checking          /RTC1 Enable fast checks (/RTCsu)
REM /RTCc Convert to smaller type checks        /RTCu Uninitialized local usage checks
REM /Gs[num] control stack checking calls       /Gh enable _penter function call
REM /GH enable _pexit function call             /GT generate fiber-safe TLS accesses
REM /Qfast_transcendentals generate inline FP intrinsics even with /fp:except
REM /homeparams Force parameters passed in registers to be written to the stack
REM /fp:<except[-]|fast|precise|strict> choose floating-point model:
REM     except[-] - consider floating-point exceptions when generating code
REM     fast - "fast" floating-point model; results are less predictable
REM     precise - "precise" floating-point model; results are predictable
REM     strict - "strict" floating-point model (implies /fp:except)
REM /clr[:option] compile for common language runtime, where option is:
REM     pure - produce IL-only output file (no native executable code)
REM     safe - produce IL-only verifiable output file
REM     oldSyntax - accept the Managed Extensions syntax from Visual C++ 2002/2003
REM     initialAppDomain - enable initial AppDomain behavior of Visual C++ 2002
REM     noAssembly - do not produce an assembly
REM -OUTPUT FILES-
REM /Fe<file> name executable file          /Fo<file> name object file
REM /Fd[file] name .PDB file                /Fi[file] name preprocessed file
REM /Fa[file] name assembly listing file    /FA[scu] configure assembly listing
REM /Fm[file] name map file                 /Fp<file> name precompiled header file
REM /Fr[file] name source browser file      /FR[file] name extended .SBR file
REM /doc[file] process XML documentation comments and optionally name the .xdc file
REM -PREPROCESSOR-
REM /D<name>{=|#}<text> define macro      /U<name> remove predefined macro
REM /u remove all predefined macros       /I<dir> add to include search path
REM /C don't strip comments               /E preprocess to stdout
REM /EP preprocess to stdout, no #line    /P preprocess to file
REM /AI<dir> add to assembly search path  /FU<file> forced using assembly/module
REM /Fx merge injected code to file       /FI<file> name forced include file
REM /X ignore "standard places"
REM -LANGUAGE-
REM /Zi enable debugging information        /Z7 enable old-style debug info
REM /Zs syntax check only                   /Za disable extensions
REM /Ze enable extensions (default)         /Zl omit default library name in .OBJ
REM /Zp[n] pack structs on n-byte boundary  /Zg generate function prototypes
REM /vd{0|1|2} disable/enable vtordisp      /vm<x> type of pointers to members
REM /Zc:arg1[,arg2] C++ language conformance, where arguments can be:
REM     forScope[-] - enforce Standard C++ for scoping rules
REM     wchar_t[-] - wchar_t is the native type, not a typedef
REM     auto[-] - enforce the new Standard C++ meaning for auto
REM     trigraphs[-] - enable trigraphs (off by default)
REM /openmp enable OpenMP 2.0 language extensions
REM -MISCELLANEOUS-
REM /MP[n] use up to 'n' processes for compilation
REM /c compile only, no link
REM /nologo suppress copyright message      /showIncludes show include file names
REM /FC use full pathnames in diagnostics   /J default char type is unsigned
REM /Wall enable all warnings               /WX treat warnings as errors
REM /TP compile all files as .cpp           /TC compile all files as .c
REM /Tc<source file> compile file as .c     /Tp<source file> compile file as .cpp
REM /bigobj generate extended object format
REM /H<num> max external name length
REM /V<string> set version string           /w disable all warnings
REM /wd<n> disable warning n                /we<n> treat warning n as an error
REM /wo<n> issue warning n once             /w<l><n> set warning level 1-4 for n
REM /W<n> set warning level (default n=1)   /WL enable one line diagnostics
REM /Yd put debug info in every .OBJ        /Y- disable all PCH options
REM /Wp64 enable 64 bit porting warnings
REM -LINKING-
REM /LD Create .DLL             /LDd Create .DLL debug library
REM /LN Create a .netmodule     /F<num> set stack size
REM /link [linker options and libraries]
REM /MD link with MSVCRT.LIB    /MT link with LIBCMT.LIB
REM /MDd link with MSVCRTD.LIB debug lib
REM /MTd link with LIBCMTD.LIB debug lib
REM -LINK OPTIONS-
REM /DEBUG         /RELEASE
REM /NOLOGO        /DLL
REM /LIBPATH:dir   /INCLUDE:symbol
REM /OUT:filename  /PDB:filename
REM /NOASSEMBLY
REM /MACHINE:{ARM|EBC|IA64|MIPS|MIPS16|MIPSFPU|MIPSFPU16|SH4|THUMB|X64|X86}
REM /SUBSYSTEM:{BOOT_APPLICATION|CONSOLE|EFI_APPLICATION|EFI_BOOT_SERVICE_DRIVER|EFI_ROM|EFI_RUNTIME_DRIVER|NATIVE|POSIX|WINDOWS|WINDOWSCE}[,#[.##]]
REM -LIB OPTIONS-
REM /NAME:filename      /DEF[:filename]
REM /ERRORREPORT:{NONE|PROMPT|QUEUE|SEND}
REM /EXPORT:symbol      /EXTRACT:membername
REM /INCLUDE:symbol     /LIBPATH:dir
REM /LIST[:filename]    /LTCG
REM /MACHINE:{ARM|EBC|IA64|MIPS|MIPS16|MIPSFPU|MIPSFPU16|SH4|THUMB|X64|X86}
REM /OUT:filename       /REMOVE:membername
REM /VERBOSE            /WX[:NO]
REM /NODEFAULTLIB[:library]     /NOLOGO
REM /SUBSYSTEM:{BOOT_APPLICATION|CONSOLE|EFI_APPLICATION|EFI_BOOT_SERVICE_DRIVER|EFI_ROM|EFI_RUNTIME_DRIVER|NATIVE|POSIX|WINDOWS|WINDOWSCE}[,#[.##]]

REM set isodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
REM echo Build script started: %isodt%

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

set common=!omni_lib_loc!\source
set odir=!omni_lib_loc!\build
set fexcep=/EHa
set source=
set fwsrc=!common!\application.cpp
set fwsrc=!fwsrc! !common!\argparser.cpp
set fwsrc=!fwsrc! !common!\async_timer.cpp
set fwsrc=!fwsrc! !common!\basic_thread.cpp
set fwsrc=!fwsrc! !common!\binary_semaphore.cpp
set fwsrc=!fwsrc! !common!\conditional.cpp
set fwsrc=!fwsrc! !common!\drop_timer.cpp
set fwsrc=!fwsrc! !common!\environment.cpp
set fwsrc=!fwsrc! !common!\externs.cpp
set fwsrc=!fwsrc! !common!\io.cpp
REM set fwsrc=!fwsrc! !common!\filesystemwatcher.cpp # incomplete
set fwsrc=!fwsrc! !common!\mutex.cpp
set fwsrc=!fwsrc! !common!\queue_timer.cpp
set fwsrc=!fwsrc! !common!\runnable.cpp
set fwsrc=!fwsrc! !common!\semaphore.cpp
REM set fwsrc=!fwsrc! !common!\socket.cpp # incomplete
set fwsrc=!fwsrc! !common!\stopwatch.cpp
set fwsrc=!fwsrc! !common!\sync_timer.cpp
set fwsrc=!fwsrc! !common!\system.cpp
set fwsrc=!fwsrc! !common!\thread.cpp
set fwsrc=!fwsrc! !common!\threadpool.cpp
set fwsrc=!fwsrc! !common!\version.cpp
set includes=/I!common!
set defines=
set prog=main.exe
set libs=
set verbose=0
set parse_only=0
set is_x64=0
set is_x86=0
set use_vsver=2012
set use_winsdk=8
set hasver=1
set vsfldr=
set winsdk=
set libpath=
set sdkinclude=
set toolchain=
set log_file=""
set use_log=0
set cleanup=0
set usedbg=0
set extraopts=
set lnkops=/NOLOGO
set syntax=0
set nowinapi=0
set doasm=0
set islib=0

:argloop
if not "%1"=="" (
    if "%1"=="-s" (
        set source=!source! %2
        shift
    ) else if "%1"=="-out" (
        set odir=%2
        shift
    ) else if "%1"=="-fw" (
        set omni_lib_loc=%2
        shift
    ) else if "%1"=="-i" (
        set tmpinc=%2
        set tmpinc=!tmpinc:/=\!
        set tmpinc=!tmpinc:\\\=\!
        set tmpinc=!tmpinc:\\=\!
        set includes=!includes! /I!tmpinc!
        shift
    ) else if "%1"=="-o" (
        set prog=%2
        shift
    ) else if "%1"=="-c" (
        set extraopts=%extraopts% "%2"
        shift
    ) else if "%1"=="-d" (
        set defines=%defines% /D %2
        shift
    ) else if "%1"=="-l" (
        set libs=!libs! %2
        shift
    ) else if "%1"=="-u" (
        set cleanup=1
    ) else if "%1"=="-single" (
        set fwsrc=!common!\library.cpp
    ) else if "%1"=="-lib" (
        set islib=1
    ) else if "%1"=="-log" (
        set log_file=%2
        set use_log=1
        shift
    ) else if "%1"=="-v" (
        set verbose=1
    ) else if "%1"=="-vv" (
        set verbose=2
    ) else if "%1"=="-vvv" (
        set verbose=3
    ) else if "%1"=="-po" (
        set parse_only=1
    ) else if "%1"=="-?" (
        goto showusage
    ) else if "%1"=="-oo" (
        REM framework options
        REM set fexcep=/EHs
        if "%2"=="stdcall" (
            set defines=!defines! /D OMNI_THREAD_STDCALL
            set extraopts=/Gz !extraopts!
        ) else if "%2"=="fastcall" (
            set defines=!defines! /D OMNI_THREAD_FASTCALL
            set extraopts=/Gr !extraopts!
        ) else if "%2"=="cdecl" (
            set defines=!defines! /D OMNI_THREAD_CDECL
            set extraopts=/Gd !extraopts!
        ) else (
            echo Unknown framework option %2
            goto showusage
        )
        shift
    ) else if "%1"=="-dbg" (
        REM framework debug options
        set usedbg=1
        if "%2"=="1" (
            set defines=!defines! /D OMNI_SHOW_DEBUG=1
        ) else if "%2"=="2" (
            set defines=!defines! /D OMNI_SHOW_DEBUG=2
        ) else if "%2"=="3" (
            set defines=!defines! /D OMNI_SHOW_DEBUG=3
        ) else if "%2"=="4" (
            set defines=!defines! /D OMNI_SHOW_DEBUG=4
        ) else if "%2"=="5" (
            set defines=!defines! /D OMNI_SHOW_DEBUG=5
        ) else if "%2"=="err" (
            set defines=!defines! /D OMNI_SHOW_DEBUG_ERR    
        ) else if "%2"=="file" (
            set defines=!defines! /D OMNI_SHOW_DEBUG_FILE
        ) else if "%2"=="func" (
            set defines=!defines! /D OMNI_SHOW_DEBUG_FUNC
        ) else if "%2"=="line" (
            set defines=!defines! /D OMNI_SHOW_DEBUG_LINE
        ) else (
            echo Unknown framework debug option %2
            goto showusage
        )
        shift
    ) else if "%1"=="-co" (
        REM compiler options
        if "%2"=="x86" (
            set is_x86=1
        ) else if "%2"=="x64" (
            set is_x64=1
        ) else if "%2"=="vs2005" (
            set use_vsver=2005
            set hasver=1
        ) else if "%2"=="vs2008" (
            set use_vsver=2008
            set hasver=1
        ) else if "%2"=="vs2010" (
            set use_vsver=2010
            set hasver=1
        ) else if "%2"=="vs2012" (
            set use_vsver=2012
            set hasver=1
        ) else if "%2"=="vs2013" (
            set use_vsver=2013
            set hasver=1
        ) else if "%2"=="vs2015" (
            set use_vsver=2015
            set hasver=1
        ) else if "%2"=="vs2017" (
            set use_vsver=2017
            set hasver=1
        ) else if "%2"=="we" (
            set extraopts=!extraopts! /WX
        ) else if "%2"=="nortti" (
            set extraopts=/GR- !extraopts!
        ) else if "%2"=="opti" (
            REM /Og is supposed to be removed from cl.exe ..
            set extraopts=/Oi !extraopts!
        ) else if "%2"=="opt1" (
            set extraopts=/O1 !extraopts!
        ) else if "%2"=="opt2" (
            set extraopts=/O2 !extraopts!
        ) else if "%2"=="opt3" (
            set extraopts=/Ox !extraopts!
        ) else if "%2"=="opts" (
            set extraopts=/Os !extraopts!
        ) else if "%2"=="asm" (
            set extraopts=/FAs !extraopts!
            set doasm=1
        ) else if "%2"=="gdb" (
            set extraopts=/Zi !extraopts!
            set cleanup=0
        ) else if "%2"=="syntax" (
            set syntax=1
            set extraopts=/Zs !extraopts!
        ) else if "%2"=="xtra" (
            set extraopts=/Wall /W4 !extraopts!
        )
        shift
    )
    shift
    goto argloop
)

if %verbose% gtr 2 (
    set lnkops=!lnkops! /VERBOSE
)

REM verify visual studio compile and link info
if %hasver% equ 0 (
    if %verbose% gtr 0 (
        echo Visual Studio version not specified, attempting to determine...
    )
    if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio\2017\Community\VC" (
        set use_vsver=2017
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 14.0\VC" (
        set use_vsver=2015
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 12.0\VC" (
        set use_vsver=2013
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 11.0\VC" (
        set use_vsver=2012
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 10.0\VC" (
        set use_vsver=2010
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 9.0\VC" (
        set use_vsver=2008
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 8\VC" (
        set use_vsver=2005
    ) else (
        echo Could not locate Visual Studio folder
        goto eeof
    )
)

if %use_vsver% equ 2005 (
    REM Visual Studio 2005
    if %verbose% gtr 1 echo Using Visual Studio 2005 v8.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio 8\VC" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio 8\VC
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 8\VC" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio 8\VC
    ) else (
        echo Could not find Visual Studio 2005 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Microsoft SDKs\Windows\v6.0\Include" (
        set winsdk="%PROGRAMFILES%\Microsoft SDKs\Windows\v6.0
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft SDKs\Windows\v6.0\Include" (
        set winsdk="%PROGRAMFILES(X86)%\Microsoft SDKs\Windows\v6.0
    ) else (
        echo Could not find Windows SDK v6
        goto eeof
    )
)
if %use_vsver% equ 2008 (
    REM Visual Studio 2008
    if %verbose% gtr 1 echo Using Visual Studio 2008 v9.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio 9.0\VC" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio 9.0\VC
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 9.0\VC" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio 9.0\VC
    ) else (
        echo Could not find Visual Studio 2008 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Microsoft SDKs\Windows\v7.0\Include" (
        set winsdk="%PROGRAMFILES%\Microsoft SDKs\Windows\v7.0
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft SDKs\Windows\v7.0\Include" (
        set winsdk="%PROGRAMFILES(X86)%\Microsoft SDKs\Windows\v7.0
    ) else (
        echo Could not find Windows SDK v7.0
        goto eeof
    )
)
if %use_vsver% equ 2010 (
    REM Visual Studio 2010
    if %verbose% gtr 1 echo Using Visual Studio 2010 v10.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio 10.0\VC" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio 10.0\VC    
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 10.0\VC" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio 10.0\VC
    ) else (
        echo Could not find Visual Studio 2010 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Microsoft SDKs\Windows\v7.1\Include" (
        set winsdk="%PROGRAMFILES%\Microsoft SDKs\Windows\v7.1
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft SDKs\Windows\v7.1\Include" (
        set winsdk="%PROGRAMFILES(X86)%\Microsoft SDKs\Windows\v7.1
    ) else (
        echo Could not find Windows SDK v7.1
        goto eeof
    )
)
if %use_vsver% equ 2012 (
    REM Visual Studio 2012
    if %verbose% gtr 1 echo Using Visual Studio 2012 v11.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio 11.0\VC" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio 11.0\VC
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 11.0\VC" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio 11.0\VC
    ) else (
        echo Could not find Visual Studio 2012 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Windows Kits\8.0\Include" (
        set winsdk="%PROGRAMFILES%\Windows Kits\8.0
    ) else if exist "%PROGRAMFILES(X86)%\Windows Kits\8.0\Include" (
        set winsdk="%PROGRAMFILES(X86)%\Windows Kits\8.0
    ) else (
        echo Could not find Windows SDK v8
        goto eeof
    )
    set use_winsdk=8
)
if %use_vsver% equ 2013 (
    REM Visual Studio 2013
    if %verbose% gtr 1 echo Using Visual Studio 2013 v12.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio 12.0\VC" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio 12.0\VC
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 12.0\VC" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio 12.0\VC
    ) else (
        echo Could not find Visual Studio 2013 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Windows Kits\8.1\Include" (
        set winsdk="%PROGRAMFILES%\Windows Kits\8.1
    ) else if exist "%PROGRAMFILES(X86)%\Windows Kits\8.1\Include" (
        set winsdk="%PROGRAMFILES(X86)%\Windows Kits\8.1
    ) else (
        echo Could not find Windows SDK v8.1
        goto eeof
    )
    set use_winsdk=8
)
if %use_vsver% equ 2015 (
    REM Visual Studio 2015
    if %verbose% gtr 1 echo Using Visual Studio 2015 v14.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio 14.0\VC" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio 14.0\VC
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio 14.0\VC" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio 14.0\VC
    ) else (
        echo Could not find Visual Studio 2015 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Windows Kits\10\Include\10.0.15063.0" (
        set winsdk="%PROGRAMFILES%\Windows Kits\10
    ) else if exist "%PROGRAMFILES(X86)%\Windows Kits\10\Include\10.0.15063.0" (
        set winsdk="%PROGRAMFILES(X86)%\Windows Kits\10
    ) else (
        echo Could not find Windows SDK v10
        goto eeof
    )
    set use_winsdk=10
)
if %use_vsver% equ 2017 (
    REM Visual Studio 2017
    if %verbose% gtr 1 echo Using Visual Studio 2017 v15.0
    if exist "%PROGRAMFILES%\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.13.26128" (
        set vsfldr="%PROGRAMFILES%\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.13.26128
    ) else if exist "%PROGRAMFILES(X86)%\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.13.26128" (
        set vsfldr="%PROGRAMFILES(X86)%\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.13.26128
    ) else (
        echo Could not find Visual Studio 2017 folder
        goto eeof
    )
    if exist "%PROGRAMFILES%\Windows Kits\10\Include\10.0.16299.0" (
        set winsdk="%PROGRAMFILES%\Windows Kits\10
    ) else if exist "%PROGRAMFILES(X86)%\Windows Kits\10\Include\10.0.16299.0" (
        set winsdk="%PROGRAMFILES(X86)%\Windows Kits\10
    ) else (
        echo Could not find Windows SDK v10
        goto eeof
    )
    set use_winsdk=101
)

if %is_x64% equ 1 (
    if %is_x86% equ 1 (
        echo Cannot specify x86 and x64 compilation
        goto eeof
    )
) else if %is_x86% equ 1 (
    if %is_x64% equ 1 (
        echo Cannot specify x86 and x64 compilation
        goto eeof
    )
) else (
    set is_x86=1
    if exist "%PROGRAMFILES(X86)%" (
        set is_x64=1
        set is_x86=0
    )
)

set sdkinclude=/I%winsdk%\Include"

if %use_winsdk% equ 8 (
    REM 2012/2013
    if exist %winsdk%\Include\km" (
        set sdkinclude=/I%winsdk%\Include\um" /I%winsdk%\Include\km" /I%winsdk%\Include\shared"
    ) else (
        set sdkinclude=/I%winsdk%\Include\um" /I%winsdk%\Include\shared"
    )
) else if %use_winsdk% equ 10 (
    REM 2015
    if exist %winsdk%\Include\10.0.15063.0\km" (
        set sdkinclude=/I%winsdk%\Include\10.0.15063.0\um" /I%winsdk%\Include\10.0.15063.0\km" /I%winsdk%\Include\10.0.15063.0\ucrt" /I%winsdk%\Include\10.0.15063.0\shared"
    ) else (
        set sdkinclude=/I%winsdk%\Include\10.0.15063.0\um" /I%winsdk%\Include\10.0.15063.0\ucrt" /I%winsdk%\Include\10.0.15063.0\shared"
    )
) else if %use_winsdk% equ 101 (
    REM 2017
    if exist %winsdk%\Include\10.0.16299.0\km" (
        set sdkinclude=/I%winsdk%\Include\10.0.16299.0\um" /I%winsdk%\Include\10.0.16299.0\km" /I%winsdk%\Include\10.0.16299.0\ucrt" /I%winsdk%\Include\10.0.16299.0\shared"
    ) else (
        set sdkinclude=/I%winsdk%\Include\10.0.16299.0\um" /I%winsdk%\Include\10.0.16299.0\ucrt" /I%winsdk%\Include\10.0.16299.0\shared"
    )
)

if %is_x64% equ 1 (
    if %use_vsver% equ 2017 (
        set toolchain=!vsfldr!\bin\Hostx64\x64\cl.exe"
        set linkchain=!vsfldr!\bin\Hostx64\x64\link.exe"
        set libchain=!vsfldr!\bin\Hostx64\x64\lib.exe"
    ) else (
        set toolchain=!vsfldr!\bin\amd64\cl.exe"
        set linkchain=!vsfldr!\bin\amd64\link.exe"
        set libchain=!vsfldr!\bin\amd64\lib.exe"
    )
    set lnkops=!lnkops! /MACHINE:X64
    if %use_winsdk% equ 8 (
        REM 2012/2013
        if exist %winsdk%\Lib\win8\km" (
            set libpath=/LIBPATH:!winsdk!\Lib\win8\km\x64" /LIBPATH:!winsdk!\Lib\win8\um\x64"
        ) else (
            set libpath=/LIBPATH:!winsdk!\Lib\win8\um\x64"
        )
    ) else if %use_winsdk% equ 10 (
        REM 2015
        if exist %winsdk%\Lib\10.0.15063.0\km" (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.15063.0\km\x64" /LIBPATH:!winsdk!\Lib\10.0.15063.0\um\x64" /LIBPATH:!winsdk!\Lib\10.0.15063.0\ucrt\x64"
        ) else (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.15063.0\um\x64" /LIBPATH:!winsdk!\Lib\10.0.15063.0\ucrt\x64"
        )
    ) else if %use_winsdk% equ 101 (
        REM 2017
        if exist %winsdk%\Lib\10.0.16299.0\km" (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.16299.0\km\x64" /LIBPATH:!winsdk!\Lib\10.0.16299.0\um\x64" /LIBPATH:!winsdk!\Lib\10.0.16299.0\ucrt\x64"
        ) else (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.16299.0\um\x64" /LIBPATH:!winsdk!\Lib\10.0.16299.0\ucrt\x64"
        )
    ) else (
        REM 2005-2010
        set libpath=/LIBPATH:!winsdk!\Lib\x64"
    )
    if %use_vsver% equ 2017 (
        set libpath=!libpath! /LIBPATH:!vsfldr!\lib\x64" /LIBPATH:!vsfldr!\atlmfc\lib\x64"
    ) else (
        set libpath=!libpath! /LIBPATH:!vsfldr!\lib\amd64" /LIBPATH:!vsfldr!\atlmfc\lib\amd64"
    )
) else if %is_x86% equ 1 (
    if %use_vsver% equ 2017 (
        set toolchain=!vsfldr!\bin\Hostx64\x86\cl.exe"
        set linkchain=!vsfldr!\bin\Hostx64\x86\link.exe"
        set libchain=!vsfldr!\bin\Hostx64\x86\lib.exe"
    ) else (
        set toolchain=!vsfldr!\bin\cl.exe"
        set linkchain=!vsfldr!\bin\link.exe"
        set libchain=!vsfldr!\bin\lib.exe"
    )
    set lnkops=!lnkops! /MACHINE:X86
    if %use_winsdk% equ 8 (
        REM 2012/2013
        if exist %winsdk%\Lib\win8\km" (
            set libpath=/LIBPATH:!winsdk!\Lib\win8\km\x86" /LIBPATH:!winsdk!\Lib\win8\um\x86"
        ) else (
            set libpath=/LIBPATH:!winsdk!\Lib\win8\um\x86"
        )
    ) else if %use_winsdk% equ 10 (
        REM 2015
        if exist %winsdk%\Lib\10.0.15063.0\km" (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.15063.0\km\x86" /LIBPATH:!winsdk!\Lib\10.0.15063.0\um\x86" /LIBPATH:!winsdk!\Lib\10.0.15063.0\ucrt\x86"
        ) else (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.15063.0\um\x86" /LIBPATH:!winsdk!\Lib\10.0.15063.0\ucrt\x86"
        )
    ) else if %use_winsdk% equ 101 (
        REM 2017
        if exist %winsdk%\Lib\10.0.16299.0\km" (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.16299.0\km\x86" /LIBPATH:!winsdk!\Lib\10.0.16299.0\um\x86" /LIBPATH:!winsdk!\Lib\10.0.16299.0\ucrt\x86"
        ) else (
            set libpath=/LIBPATH:!winsdk!\Lib\10.0.16299.0\um\x86" /LIBPATH:!winsdk!\Lib\10.0.16299.0\ucrt\x86"
        )
    ) else (
        REM 2005-2010
        set libpath=/LIBPATH:!winsdk!\Lib"
    )
    if %use_vsver% equ 2017 (
        set libpath=!libpath! /LIBPATH:!vsfldr!\lib\x86" /LIBPATH:!vsfldr!\atlmfc\lib\x86"
    ) else (
        set libpath=!libpath! /LIBPATH:!vsfldr!\lib" /LIBPATH:!vsfldr!\atlmfc\lib"
    )
    REM __stdcall is for 32-bit and SDK < 7.1
    set defines=!defines! /D OMNI_THREAD_STDCALL
)
REM end visual studio checks

if "%source%" == "" (
    set islib=1
)

if %usedbg% equ 1 (
    set lnkops=!lnkops! /DEBUG
) else (
    set lnkops=!lnkops!
)
if %nowinapi% equ 1 (
    REM /MD link with MSVCRT.LIB
    set extraopts=/MD !extraopts!
) else (
    REM /MT link with LIBCMT.LIB
    set extraopts=/MT !extraopts!
)

set includes=!includes! !sdkinclude! /I!vsfldr!\Include"
set extraopts=/nologo /TP !fexcep! !extraopts!
set lnkops=!lnkops! !libpath!

set binfldr=!odir!\bin
set objdir=!odir!\obj
set asmdir=!odir!\asm
set utofile=!binfldr!\omni.lib

if not exist %objdir% (
    echo mkdir %objdir%
    mkdir %objdir%
)
if not exist %asmdir% (
    echo mkdir %asmdir%
    mkdir %asmdir%
)

if %cleanup% equ 1 (
    echo.
    echo Removing old files
    echo.
    
    if exist %utofile% (
        if %verbose% gtr 0 (
            echo del !utofile!
        )
        if %parse_only% equ 0 (
            del !utofile!
        )
    )
    if exist %prog% (
        if %verbose% gtr 0 (
            echo del !prog!
        )
        if %parse_only% equ 0 (
            del !prog!
        )
    )
    if exist %objdir% (
        if %verbose% gtr 0 (
            echo del !objdir!\*.obj
        )
        if %parse_only% equ 0 (
            del !objdir!\*.obj
        )
    )
    if exist %asmdir% (
        if %verbose% gtr 0 (
            echo del !asmdir!\*.asm
        )
        if %parse_only% equ 0 (
            del !asmdir!\*.asm
        )
    )
    if %use_log% equ 1 (
        if %verbose% gtr 0 (
            echo del !log_file!
        )
        if %parse_only% equ 0 (
            del !log_file!
        )
    )
)

if %verbose% gtr 1 (
    echo ---Settings---
    echo Toolchain: !toolchain!
    echo Linkchain: !linkchain!
    echo Libchain: !libchain!
    echo VS Folder: !vsfldr!"
    echo Win SDK: !winsdk!"
    echo Lib Path: !libpath!
    echo Prog name: !prog!
    echo Defines: !defines!
    echo Includes: !includes!
    echo Extra Opts: !extraopts!
    echo Libs: !libs!
    echo Log file: "!log_file!"
    echo.
)
if %verbose% gtr 2 (
    echo ---Source Files---
    echo !source!
    echo.
)

REM %toolchain% %source% %defines% %includes% %extraopts% /link %libpath% %libs% 1>>%log_file% 2>&1
if %islib% equ 0 (
    set source=!source! !fwsrc!
) else (
    set cisodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
    echo !cisodt!: Compiling Omni object files ...
    set lnklist=
    for %%s in (%fwsrc%) do (
        set srcname=%%s
        set srcf=!srcname!
        set srcname=%objdir%\%%~ns.obj
        set asmopt=
        set lnklist=!lnklist! !srcname!
        if %doasm% equ 1 (
            set asmopt=/Fa%asmdir%\%%~ns.asm
        )
        if %verbose% gtr 0 (
            if %verbose% gtr 1 (
                if %use_log% equ 1 (
                    echo !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts! "1>>!log_file! 2>&1"
                ) else (
                    echo !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts!
                )
            ) else (
                echo %%s
            )
        )
        if %parse_only% equ 0 (
            if %use_log% equ 1 (
                !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts! 1>>!log_file! 2>&1
            ) else (
                if %verbose% gtr 0 (
                    REM becuase this spits out the filename it's compiling, we send that output to NUL
                    !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts! >NUL
                ) else (
                    !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts!
                )
                
            )
        )
    )

    if %syntax% equ 0 (
        echo.
        set lcompchain=!libchain!
        set lisodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
        echo !lisodt!: Linking object files into library ...
        if %usedbg% equ 1 (
            if %use_log% equ 1 (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs! "1>>!log_file! 2>&1"
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs! 1>>!log_file! 2>&1
                )
            ) else (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs!
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs!
                )
            )
        ) else (
            if %use_log% equ 1 (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs! "1>>!log_file! 2>&1"
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs! 1>>!log_file! 2>&1
                )
            ) else (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs!
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!utofile! !libs!
                )
            )
        )
        REM end link
        echo.
        if %parse_only% equ 0 (
            set bisodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
            echo !bisodt!: Build status for !utofile!
            if exist !utofile! (
                echo SUCCESS
            ) else (
                echo FAIL
            )
        )
    )
)
echo.
if not "%source%" == "" (
    set cisodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
    echo !cisodt!: Compiling program source ...
    set lnklist=
    for %%s in (%source%) do (
        set srcname=%%s
        set srcf=!srcname!
        set srcname=%objdir%\%%~ns.obj
        set asmopt=
        set lnklist=!lnklist! !srcname!
        if %doasm% equ 1 (
            set asmopt=/Fa%asmdir%\%%~ns.asm
        )
        if %verbose% gtr 0 (
            if %verbose% gtr 1 (
                if %use_log% equ 1 (
                    echo !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts! "1>>!log_file! 2>&1"
                ) else (
                    echo !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts!
                )
            ) else (
                echo %%s
            )
        )
        if %parse_only% equ 0 (
            if %use_log% equ 1 (
                !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts! 1>>!log_file! 2>&1
            ) else (
                if %verbose% gtr 0 (
                    REM becuase this spits out the filename it's compiling, we send that output to NUL
                    !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts! >NUL
                ) else (
                    !toolchain! /c !srcf! /Fo!srcname! !asmopt! !defines! !includes! !extraopts!
                )
                
            )
        )
    )
    REM end compile

    if %syntax% equ 0 (
        echo.
        
        set lcompchain=!linkchain!
        if %islib% equ 1 (
            set libs=!libs! omni.lib
            set lnkops=!lnkops! /LIBPATH:!binfldr!
        )
        set lisodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
        echo !lisodt!: Linking program object files ...
        
        if %usedbg% equ 1 (
            if %use_log% equ 1 (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs! "1>>!log_file! 2>&1"
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs! 1>>!log_file! 2>&1
                )
            ) else (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs!
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs!
                )
            )
        ) else (
            if %use_log% equ 1 (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs! "1>>!log_file! 2>&1"
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs! 1>>!log_file! 2>&1
                )
            ) else (
                echo !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs!
                if %parse_only% equ 0 (
                    !lcompchain! !lnklist! !lnkops! /OUT:!prog! !libs!
                )
            )
        )
        REM end link

        echo.
        if %parse_only% equ 0 (
            set bisodt=%date:~10,4%-%date:~4,2%-%date:~7,2% %time:~0,2%:%time:~3,2%:%time:~6,2%
            echo !bisodt!: Build status for !prog!
            if exist !prog! (
                echo SUCCESS
            ) else (
                echo FAIL
            )
        )
    ) else (
        echo.
        echo Syntax check complete
    )
)

echo.
goto eeof

:showusage
echo usage: compile [options]
echo.
echo OPTIONS:
echo compile script options:
echo        -s [source] The main source file(s) to compile (files other than
echo                    the framework source). If this flag is not set, this
echo                    script will build Omni as a library.
echo                    Specified source must be enclosed in quotes \"\" and
echo                    seperated by spaces.
echo                    Example:
echo                    compile -s \"file1.cpp file2.cpp file3.cpp\" -o main
echo        -fw [path]  The Omni Framework path (default of '%omni_lib_loc%')
echo        -out [path] The output build path to put the obj/asm files
echo        -i [path]   Includes [path] in the compiler include path
echo        -o [name]   The file you wish to compile (without an extension)
echo        -c [opts]   Pass extra arguments to the compiler
echo        -d [define] Pass extra defines to the compiler
echo        -l          Use extra libs (%extralibs%)
echo        -u          Specifying this will clean up any .o files
echo        -single     Specifying this will build library.cpp (single file framework)
echo        -lib        Specifying this will compile as a library instead of an executable
echo        -log [log]  Write console output to a log file
echo        -elog [log] Write the error log to [log], default
echo        -v          Show verbose output (-v = 1, -vv = 2, -vvv = 3)
echo        -po         Parse the compile script only
echo        -oo [ops]   Enables framework features
echo        -dbg [ops]  Enables framework debug features
echo        -co [ops]   Enables compiler/linker features
echo.
echo framework options (-oo):
echo        stdcall     Defines the thread calling convention to be of stdcall
echo        fastcall    Defines the thread calling convention to be of fastcall
echo        cdecl       Defines the thread calling convention to be of cdecl
echo.
echo framework debug options (-dbg):
echo        1           Defines the OMNI_SHOW_DEBUG=1
echo        2           Defines the OMNI_SHOW_DEBUG=2
echo        3           Defines the OMNI_SHOW_DEBUG=3
echo        4           Defines the OMNI_SHOW_DEBUG=4
echo        5           Defines the OMNI_SHOW_DEBUG=5
echo        err         Defines the OMNI_SHOW_DEBUG_ERR
echo        file        Defines the OMNI_SHOW_DEBUG_FILE
echo        func        Defines the OMNI_SHOW_DEBUG_FUNC
echo        line        Defines the OMNI_SHOW_DEBUG_LINE
echo.
echo compiler options (-co):
echo        x86         Enable 32-bit compilation
echo        x64         Enable 64-bit compilation
echo        we          Treat all warnings as errors
echo        se          Stop on first error (instead of trying to continue)
echo        xtra        Use the extra compiler/linker flags (can generate erroneous errors)
echo        nortti      Disables RTTI (run-time type information) for C++
echo        opti        Enable global optimization with intrinsic functions (/Oi /Og)
echo        opt1        Enable optimizations (/O1)
echo        opt2        Enable more optimizations (/O2)
echo        opt3        Maximum optimizations (/Ox)
echo        opts        Favor code space (/Os)
echo        asm         Generate the assembly output (/FAs, .asm file name)
echo        gdb         Sets the /Zi flag, enabling debug output
echo        syntax      Sets the /Zs flag which checks the code for syntax
echo                    errors only and does nothing beyond that
echo        vs2005      Specifies to use Visual Studio 2005 (v8.0) and WinSDK 6
echo        vs2008      Specifies to use Visual Studio 2008 (v9.0) and WinSDK 7
echo        vs2010      Specifies to use Visual Studio 2010 (v10.0) and WinSDK 7.1
echo        vs2012      Specifies to use Visual Studio 2012 (v11.0) and WinSDK 8.0
echo        vs2013      Specifies to use Visual Studio 2013 (v12.0) and WinSDK 8.1
echo        vs2015      Specifies to use Visual Studio 2015 (v14.0) and WinSDK 10.0.15063.0
echo        vs2017      Specifies to use Visual Studio 2017 (v15.0) and WinSDK 10.0.16299.0
echo.
echo Note: since certain portions of Omni are header only, due to template specializations
echo and other C++ specific issues, if you compile Omni as a library with certain preprocessor
echo options on, remember to keep those same options defined when building your other source
echo that references the Omni library. Not doing this can result in undefined behavior (see
echo the virtual thunk note).
goto eeof

:eeof
endlocal
:eof
