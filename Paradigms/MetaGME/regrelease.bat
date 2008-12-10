@echo off
REM	 
REM	Release Builder depends on this script
REM
REM	Please consult with Peter before editing this file
REM 

echo MetaDecorator.dll:
regsvr32 /s "MetaDecorator\Release\MetaDecorator.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MONTraverser.dll:
regsvr32 /s "MONTraverser\Release\MONTraverser.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo BonExtender2004.dll:
regsvr32 /s "BONExtension\Release\BonExtender2004.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MetaInterpreter.dll:
regsvr32 /s "MetaInterpreter\Release\MetaInterpreter.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo NamespaceConfig.dll:
regsvr32 /s "NamespaceConfigure\Release\NamespaceConfig.dll"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occured. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof
