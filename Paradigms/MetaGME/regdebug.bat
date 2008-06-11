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

echo MONTraverser.dll:
regsvr32 /s "MONTraverser\Debug\MONTraverser.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo BonExtender2004.dll:
regsvr32 /s "BONExtension\Debug\BonExtender2004.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MetaInterpreter2004.dll:
regsvr32 /s "MetaInterpreter2004\Debug\MetaInterpreter2004.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo NamespaceConfig.dll:
regsvr32 /s "NamespaceConfigure\Debug\NamespaceConfig.dll"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occured. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof