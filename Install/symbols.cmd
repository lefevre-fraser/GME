set VERSION=10.6.29
set DBGTOOLS=C:\Program Files\Debugging Tools for Windows (x64)
"%DBGTOOLS%\symstore.exe" add /f %GME_ROOT%/Install/GME-%VERSION%-symbols /s \\atlantis\project\GME\symbols /r /t GME /v %VERSION% /c "GME Release %VERSION% symbols added" /compress