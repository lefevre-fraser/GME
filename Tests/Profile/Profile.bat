call C:\progra~1\micros~1\vc98\bin\vcvars32.bat
echo on

copy ..\core\profile\core.dll .
copy ..\core\profile\core.map .
copy ..\meta\profile\meta.dll .
copy ..\meta\profile\meta.map .
copy ..\mga\profile\mga.dll .
copy ..\mga\profile\mga.map .
copy ..\gme\release\GME.exe .

prep.exe /om /ft /oi GME /ot GME core.dll meta.dll mga.dll

copy core._ll core.dll
copy meta._ll meta.dll
copy mga._ll mga.dll

regsvr32 /s /c core.dll
regsvr32 /s /c meta.dll
regsvr32 /s /c mga.dll

profile.exe /I GME /O GME GME

prep.exe /m GME

plist.exe GME >GME.txt

start notepad GME.txt
