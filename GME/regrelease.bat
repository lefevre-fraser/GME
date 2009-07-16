@echo off
REM	 
REM	Release Builder depends on this script
REM
REM	Please consult with Peter before editing this file
REM 

echo Core.dll:
regsvr32 /s "Core\Release\Core.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Meta.dll:
regsvr32 /s "Meta\Release\Meta.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Mga.dll:
regsvr32 /s "Mga\Release\Mga.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MgaUtil.dll:
regsvr32 /s "MgaUtil\Release\MgaUtil.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Parser.dll:
regsvr32 /s "Parser\Release\Parser.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo ConstraintManager.dll:
regsvr32 /s "ConstraintManager\Release\ConstraintManager.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo GMEActiveBrowser.ocx:
regsvr32 /s "GMEActiveBrowser\Release\GMEActiveBrowser.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo MgaDecorators.dll:
regsvr32 /s "MgaDecorators\Release\MgaDecorators.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Annotator.dll:
regsvr32 /s "Annotator\Release\Annotator.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo ObjectInspector.ocx:
regsvr32 /s "ObjectInspector\Release\ObjectInspector.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo Search.ocx:
regsvr32 /s "Search\Release\Search.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo Console.ocx:
regsvr32 /s "Console\Release\Console.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo XmlBackEnd.dll:
regsvr32 /s "XmlBackEnd\Release\XmlBackEnd.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo PartBrowser.ocx:
regsvr32 /s "PartBrowser\Release\PartBrowser.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo PanningView.ocx:
regsvr32 /s "PanningView\Release\PanningView.ocx"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occured. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof