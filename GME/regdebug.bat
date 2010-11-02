@echo off
REM	 
REM	Release Builder depends on this script
REM
REM	Please consult with Peter before editing this file
REM 

echo Core.dll:
regsvr32 /s "%~dp0Debug\Core.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Meta.dll:
regsvr32 /s "%~dp0Debug\Meta.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Mga.dll:
regsvr32 /s "%~dp0Debug\Mga.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo MgaUtil.dll:
regsvr32 /s "%~dp0Debug\MgaUtil.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Parser.dll:
regsvr32 /s "%~dp0Debug\Parser.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo ConstraintManager.dll:
regsvr32 /s "%~dp0Debug\ConstraintManager.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo GMEActiveBrowser.ocx:
regsvr32 /s "%~dp0Debug\GMEActiveBrowser.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo MgaDecorators.dll:
regsvr32 /s "%~dp0Debug\MgaDecorators.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo Annotator.dll:
regsvr32 /s "%~dp0Debug\Annotator.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo ObjectInspector.ocx:
regsvr32 /s "%~dp0Debug\ObjectInspector.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo Search.ocx:
regsvr32 /s "%~dp0Debug\Search.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo Console.ocx:
regsvr32 /s "%~dp0Debug\Console.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo XmlBackEnd.dll:
regsvr32 /s "%~dp0Debug\XmlBackEnd.dll"
if errorlevel 1 goto errorlabel
echo    OK

echo PartBrowser.ocx:
regsvr32 /s "%~dp0Debug\PartBrowser.ocx"
if errorlevel 1 goto errorlabel
echo    OK

echo PanningView.ocx:
regsvr32 /s "%~dp0Debug\PanningView.ocx"
if errorlevel 1 goto errorlabel
echo    OK

goto eof

:errorlabel
set tlevel=%ERRORLEVEL%
echo Error occurred. Code: %ERRORLEVEL%
pause
exit /b %tlevel%

:eof
