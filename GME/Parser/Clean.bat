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
%RF% Parser.aps
%RF% Parser.plg
%RF% ParserLib.h
%RF% ParserLib.tlb
%RF% ParserLib_i.c
%RF% ParserLib_p.c
%RF% dlldata.c
