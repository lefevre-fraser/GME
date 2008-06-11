call C:\progra~1\micros~1\vc98\bin\vcvars32.bat
echo on
REM copy ..\coretest\coretest.exe profile
copy ..\gme\release\gme.exe profile
cd profile
copy core.dll core.sav
prep /om /ft core.dll
copy core._ll core.dll
regsvr32 /s /c core.dll
profile /I core /O core gme
prep /m core
plist core >core.txt
copy core.sav core.dll
start notepad core.txt
