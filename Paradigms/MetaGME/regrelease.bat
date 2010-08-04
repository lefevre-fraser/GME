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

echo BonExtender.dll:
regsvr32 /s "BonExtender\Release\BonExtender.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MetaInterpreter.dll:
regsvr32 /s "MetaInterpreter\Release\MetaInterpreter.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo NamespaceConfig.dll:
regsvr32 /s "NamespaceConfig\Release\NamespaceConfig.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MetaMAid.dll:
regsvr32 /s "MetaMAid\Release\MetaMAid.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo QuRep.dll:
regsvr32 /s "QuRep\Release\QuRep.dll"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occurred. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof
