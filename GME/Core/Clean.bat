if "%OS%" == "Windows_NT" goto winnt
:win95
set RF=DEL /Q
set RD=DELTREE /Y
goto main
:winnt
set RF=DEL /Q
set RD=RMDIR /S /Q
:main
%RD% Debug
%RD% Release
%RD% Profile
%RF% Core.aps
%RF% Core.plg
%RF% CoreLib.h
%RF% CoreLib.tlb
%RF% CoreLib_i.c
%RF% CoreLib_p.c
%RF% dlldata.c
