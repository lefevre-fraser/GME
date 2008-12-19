@echo off
REM	 
REM	Release Builder depends on this script
REM
REM	Please consult with Peter before editing this file
REM 

echo Core.dll:
regsvr32 /s "Core\Debug\Core.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Meta.dll:
regsvr32 /s "Meta\Debug\Meta.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Mga.dll:
regsvr32 /s "Mga\Debug\Mga.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MgaUtil.dll:
regsvr32 /s "MgaUtil\Debug\MgaUtil.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Parser.dll:
regsvr32 /s "Parser\Debug\Parser.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo ConstraintManager.dll:
regsvr32 /s "ConstraintManager\Debug\ConstraintManager.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo GMEActiveBrowser.ocx:
regsvr32 /s "GMEActiveBrowser\Debug\GMEActiveBrowser.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo MgaDecorators.dll:
regsvr32 /s "MgaDecorators\Debug\MgaDecorators.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Annotator.dll:
regsvr32 /s "Annotator\Debug\Annotator.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo ObjectInspector.ocx:
regsvr32 /s "ObjectInspector\Debug\ObjectInspector.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo Search.ocx:
regsvr32 /s "Search\Debug\Search.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo Console.ocx:
regsvr32 /s "Console\Debug\Console.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo XmlBackEnd.dll:
regsvr32 /s "XmlBackEnd\Debug\XmlBackEnd.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo PartBrowser.ocx:
regsvr32 /s "PartBrowser\Debug\PartBrowser.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo PanningView.ocx:
regsvr32 /s "PanningView\Debug\PanningView.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo GMEView.ocx:
regsvr32 /s "GMEView\Debug\GMEView.ocx"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occured. Code: %ERRORLEVEL%
pause
exit %tlevel%

:eof