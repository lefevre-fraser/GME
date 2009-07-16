call C:\progra~1\micros~1\vc98\bin\vcvars32.bat
echo on
copy ..\metatest\metatest.exe profile
copy ..\core\profile\core.dll profile
copy ..\core\profile\core.map profile
cd profile
copy core.dll core.sav
prep /om /ft core.dll
copy core._ll core.dll
regsvr32 /s /c core.dll
regsvr32 /s /c meta.dll
profile /I core /O core metatest
prep /m core
plist core >core.txt
copy core.sav core.dll
start notepad core.txt
