@echo off
setlocal enabledelayedexpansion

set odir=C:\Code\omni
set sodir=%odir%\source\omni
set base=%odir%\tools\delegate_maker
set tfile=%base%\template.hpp
set lfile=%odir%\docugen\license.txt

set dlmkr=%base%\delmkr.vbs -f %tfile% -d %sodir% -n 16 -le n -l %lfile%

echo !dlmkr!
!dlmkr!

:eeof
endlocal
:eof
