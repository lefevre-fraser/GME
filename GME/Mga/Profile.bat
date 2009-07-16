call C:\progra~1\micros~1\vc98\bin\vcvars32.bat
echo on
copy ..\gme\release\GME.exe profile
cd profile
copy mga.dll mga.sav
prep /om /ft mga.dll
copy mga._ll mga.dll
regsvr32 /s /c mga.dll
profile /I mga /O mga GME
prep /m mga
plist mga >mga.txt
copy mga.sav mga.dll
start notepad mga.txt
