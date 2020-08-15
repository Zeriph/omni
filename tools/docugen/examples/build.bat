@echo off
setlocal enabledelayedexpansion
set gcc="C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64\cl.exe"
set inc=/I"C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include" /I"C:\Program Files (x86)\Windows Kits\8.1\Include\um" /I"C:\Program Files (x86)\Windows Kits\8.1\Include\km" /I"C:\Program Files (x86)\Windows Kits\8.1\Include\shared"
set ops=/D NDEBUG /D _CONSOLE /D _UNICODE /D UNICODE /EHa /link /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib\amd64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x64"
G:\tools\docugen\examples

set exdir=G:\tools\docugen\examples\classes
set fwexd=G:\tools\docugen\examples\library
set zloc=G:\source
set zsrc=%zloc%\library.cpp
set zout=G:\tools\docugen\bin\examples\%1.exe
set xfile="%exdir%\%1.cpp"
set zexd=/DOMNI_SHOW_DEBUG=5 /DOMNI_SHOW_DEBUG_ERR /DOMNI_SHOW_DEBUG_FILE /DOMNI_SHOW_DEBUG_FUNC /DOMNI_SHOW_DEBUG_LINE
set zexf=/DOMNI_UT_FULL /DOMNI_SHOW_DEBUG=5 /DOMNI_SHOW_DEBUG_ERR /DOMNI_SHOW_DEBUG_FILE /DOMNI_SHOW_DEBUG_FUNC /DOMNI_SHOW_DEBUG_LINE /DOMNI_DISPOSE_EVENT /DOMNI_OBJECT_NAME /DOMNI_TYPE_INFO /DOMNI_SAFE_LIBRARY /DOMNI_NON_PORTABLE /DOMNI_COMPILE_FLAGS

if "%1"=="list" (
    dir /b !exdir!\*.cpp
    goto eeof
) else if "%1"=="base" (
    set xfile="base.cpp"
) else if "%1"=="fw" (
    if "%2"=="list" (
        dir /ad /b !fwexd!\
        goto eeof
    )
    set xfile=%fwexd%\%2\example.cpp
)

if not exist !xfile! (
    echo Example file not found: !xfile!
) else (
    set compilecmd=""
    if "%2"=="debug" (
        set compilecmd=!gcc! !xfile! !zsrc! /I!zloc! !zexd! /Fe!zout! !inc! !ops!
    ) else if "%2"=="full" (
        set compilecmd=!gcc! !xfile! !zsrc! /I!zloc! !zexf! /Fe!zout! !inc! !ops!
    ) else if "%2"=="nolib" (
        set compilecmd=!gcc! !xfile! /I!zloc! /Fe!zout! !inc! !ops!
    ) else if "%2"=="fullnl" (
        set compilecmd=!gcc! !xfile! /I!zloc! !zexf! /Fe!zout! !inc! !ops!
    ) else (
        set compilecmd=!gcc! !xfile! !zsrc! /I!zloc! /Fe!zout! !inc! !ops!
    )
    echo Invoking: !compilecmd!
    !compilecmd!
    del *.obj
)

:eeof
endlocal
