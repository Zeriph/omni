@echo off
set cmd=g++ base.cpp ..\source\library.cpp  /Febin\base.exe /D NDEBUG /D _CONSOLE /D _UNICODE /D UNICODE /D OMNI_DISPOSE_EVENT /D OMNI_OBJECT_NAME /D OMNI_TYPE_INFO /D OMNI_SAFE_FRAMEWORK /D OMNI_NON_PORTABLE /D OMNI_COMPILE_FLAGS /I ..\source /I. /O2
echo %cmd%
%cmd%
