@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by INTERPRETERCONFIG.HPJ. >"hlp\InterpreterConfig.hm"
echo. >>"hlp\InterpreterConfig.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\InterpreterConfig.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\InterpreterConfig.hm"
echo. >>"hlp\InterpreterConfig.hm"
echo // Prompts (IDP_*) >>"hlp\InterpreterConfig.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\InterpreterConfig.hm"
echo. >>"hlp\InterpreterConfig.hm"
echo // Resources (IDR_*) >>"hlp\InterpreterConfig.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\InterpreterConfig.hm"
echo. >>"hlp\InterpreterConfig.hm"
echo // Dialogs (IDD_*) >>"hlp\InterpreterConfig.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\InterpreterConfig.hm"
echo. >>"hlp\InterpreterConfig.hm"
echo // Frame Controls (IDW_*) >>"hlp\InterpreterConfig.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\InterpreterConfig.hm"
REM -- Make help for Project INTERPRETERCONFIG


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\InterpreterConfig.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\InterpreterConfig.hlp" goto :Error
if not exist "hlp\InterpreterConfig.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\InterpreterConfig.hlp" Debug
if exist Debug\nul copy "hlp\InterpreterConfig.cnt" Debug
if exist Release\nul copy "hlp\InterpreterConfig.hlp" Release
if exist Release\nul copy "hlp\InterpreterConfig.cnt" Release
echo.
goto :done

:Error
echo hlp\InterpreterConfig.hpj(1) : error: Problem encountered creating help file

:done
echo.
