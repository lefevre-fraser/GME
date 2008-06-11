@echo off
REM
REM Boot program for the release building scripts
REM
REM Author: Peter Volgyesi (peter.volgyesi@vanderbilt.edu)
REM

REM	 
REM	Check python interpreter
REM 

python -h >NUL
if errorlevel 1 goto pythonnotfounderror

REM	 
REM	Build components
REM 

pushd Install\Build
build.py %1 %2 %3 %4 %5 %6 %7 %8
popd
goto eof

:pythonnotfounderror
echo No python interpreter found!
echo You can download ActivePython from http://www.python.org/download/
goto eof

:eof

