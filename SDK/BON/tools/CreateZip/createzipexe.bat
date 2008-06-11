@echo off
REM	 
REM	Release Builder depends on this script
REM
REM	Please consult with Peter before editing this file
REM 

cd ..\..
set ZZ=tools\CreateNewComponent.zip
echo Copy ConfigureComponent.exe:
copy tools\ComponentConfig\Release\ConfigureComponent.exe .
if errorlevel 1 goto errorlabel
echo    OK

echo Deleting previous resource and exe files 
del %ZZ%
del tools\CreateNewComponent\Release\CreateNewComponent.res
rem del tools\CreateNewComponent\Release\CreateNewComponent.exe
echo (No problem if some files to be deleted are not found)

echo Creating ZIP archive:
"..\..\Install\Build\zip.exe" -9 -r -i@packagefiles.lst %ZZ% .
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occured. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof