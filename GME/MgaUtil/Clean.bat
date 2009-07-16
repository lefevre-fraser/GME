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
%RF% dlldata.c
%RF% MgaUtil.aps
%RF% MgaUtil.plg
%RF% MgaUtilLib.h
%RF% MgaUtilLib_i.c
%RF% MgaUtilLib_p.c
%RF% MgaUtilLib.tlb
