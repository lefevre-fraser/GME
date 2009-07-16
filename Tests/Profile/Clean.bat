if "%OS%" == "Windows_NT" goto winnt
:win95
set RF=DEL /Q
set RD=DELTREE /Y
goto main
:winnt
set RF=DEL /Q
set RD=RMDIR /S /Q
:main
%RF% Core.*
%RF% Meta.*
%RF% Mga.*
%RF% GME.*
