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
%RF% Meta.aps
%RF% Meta.plg
%RF% MetaLib.h
%RF% MetaLib.tlb
%RF% MetaLib_i.c
%RF% MetaLib_p.c
%RF% dlldata.c
