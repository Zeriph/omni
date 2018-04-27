@echo off
setlocal enabledelayedexpansion
set exdir=G:\examples\classes
set fwexd=G:\examples\framework
set zloc=G:\source
set zsrc=%zloc%\library.cpp
set zout=bin\%1.exe
set xfile="%exdir%\%1.cpp"
set zexd=/DOMNI_SHOW_DEBUG=5 /DOMNI_SHOW_DEBUG_ERR /DOMNI_SHOW_DEBUG_FILE /DOMNI_SHOW_DEBUG_FUNC /DOMNI_SHOW_DEBUG_LINE
set zexf=/DOMNI_UT_FULL /DOMNI_SHOW_DEBUG=5 /DOMNI_SHOW_DEBUG_ERR /DOMNI_SHOW_DEBUG_FILE /DOMNI_SHOW_DEBUG_FUNC /DOMNI_SHOW_DEBUG_LINE /DOMNI_DISPOSE_EVENT /DOMNI_OBJECT_NAME /DOMNI_TYPE_INFO /DOMNI_SAFE_FRAMEWORK /DOMNI_NON_PORTABLE /DOMNI_COMPILE_FLAGS
set ccc=g++

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
) else if "%1"=="64" (
    set xfile="%exdir%\%2.cpp"
    set zout=bin\%2.exe
    set ccc=g++64
)

if not exist !xfile! (
    echo Example file not found: !xfile!
) else (
    set compilecmd=""
    if "%2"=="debug" (
        set compilecmd=!ccc! !xfile! !zsrc! /I!zloc! !zexd! /Fe!zout!
    ) else if "%2"=="full" (
        set compilecmd=!ccc! !xfile! !zsrc! /I!zloc! !zexf! /Fe!zout!
    ) else if "%2"=="nolib" (
        set compilecmd=!ccc! !xfile! /I!zloc! /Fe!zout!
    ) else if "%2"=="fullnl" (
        set compilecmd=!ccc! !xfile! /I!zloc! !zexf! /Fe!zout!
    ) else (
        set compilecmd=!ccc! !xfile! !zsrc! /I!zloc! /Fe!zout!
    )
    echo Invoking: !compilecmd!
    !compilecmd!
    del *.obj
)

:eeof
endlocal
