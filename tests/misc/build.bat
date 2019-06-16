@echo off
set odir=G:
set tdir=%odir%\tests
set gcc="C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64\cl.exe"
set inc=/I"C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include" /I"C:\Program Files (x86)\Windows Kits\8.1\Include\um" /I"C:\Program Files (x86)\Windows Kits\8.1\Include\km" /I"C:\Program Files (x86)\Windows Kits\8.1\Include\shared"
set ops=/D NDEBUG /D _CONSOLE /D _UNICODE /D UNICODE /EHa /link /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib\amd64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x64"
set flags=/D OMNI_DISPOSE_EVENT /D OMNI_OBJECT_NAME /D OMNI_TYPE_INFO /D OMNI_SAFE_FRAMEWORK /D OMNI_NON_PORTABLE
set cmd=%gcc% %tdir%\misc\base.cpp %odir%\source\library.cpp %flags% /I %odir%\source /O2 /Fe%tdir%\bin\base.exe %inc% %ops%
echo %cmd% %*
call %cmd% %*
