set VERSION=10.1.11
set DBGTOOLS=C:\Program Files\Debugging Tools for Windows (x64)
"%DBGTOOLS%\symstore.exe" add /f %GME_ROOT%/Install/symbols /s \\atlantis\project\GME\symbols /r /t GME /v %VERSION% /c "GME Release %VERSION% symbols added" /compress