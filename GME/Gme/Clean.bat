if "%OS%" == "Windows_NT" goto winnt
:win95
set RF=DEL /Q
set RD=DELTREE /Y
goto main
:winnt
set RF=DEL /Q
set RD=RMDIR /S /Q
:main

%RF% MGA.ncb
%RD% Debug
%RD% Release
%RD% Profile

%RD% Mga\Debug
%RD% Mga\Release
%RD% Mga\Profile
%RF% Mga\MgaLib.tlb
%RF% Mga\MgaLib.h
%RF% Mga\MgaLib_i.c
%RF% Mga\Mga.plg
%RF% Mga\Mga.aps

CD Core
CALL Clean.bat
CD ..\CoreTest
CALL Clean.bat
CD ..\Meta
CALL Clean.bat
CD ..\MetaTest
CALL Clean.bat
CD ..\Parser
CALL Clean.bat
CD ..\Common
CALL Clean.bat
CD ..\Interfaces
CALL Clean.bat
CD ..\MgaUtil
CALL Clean.bat
CD ..\Install
CALL Clean.bat
CD ..

%RD% Browser\Debug
%RD% Browser\Release
%RF% Browser\ActiveBrowser.plg
%RF% Browser\ActiveBrowser.aps
%RF% Browser\ActiveBrowser_i.h
%RF% Browser\ActiveBrowser_i.c
%RF% Browser\ActiveBrowser_p.c
%RD% BrowserTest\Debug
%RD% BrowserTest\Release
%RD% BrowserTest\ActiveBrowserTest\Debug
%RD% BrowserTest\ActiveBrowserTest\Release

%RD% Gme\Debug
%RD% Gme\Release
%RF% Gme\GME.plg
%RF% Gme\GME.aps
%RF% Gme\GME_i.c
%RF% Gme\GMEi.h

%RD% InterpreterTest\Debug
%RD% InterpreterTest\Release
