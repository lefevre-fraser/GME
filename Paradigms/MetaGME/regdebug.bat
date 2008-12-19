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

echo MetaMAid.dll:
regsvr32 /s "MetaMAid\Debug\MetaMAid.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo QuRep.dll:
regsvr32 /s "QuRep\Debug\QuRep.dll"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occured. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof