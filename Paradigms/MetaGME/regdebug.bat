@echo off
REM	 
REM	Release Builder depends on this script
REM
REM	Please consult with Peter before editing this file
REM 

echo MetaDecorator.dll:
regsvr32 /s "MetaDecorator\Debug\MetaDecorator.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo BonExtender.dll:
regsvr32 /s "BonExtender\Debug\BonExtender.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MetaInterpreter.dll:
regsvr32 /s "MetaInterpreter\Debug\MetaInterpreter.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo NamespaceConfig.dll:
regsvr32 /s "NamespaceConfig\Debug\NamespaceConfig.dll"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occurred. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof
