# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Mdemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Mdemo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Mdemo - Win32 Release" && "$(CFG)" != "Mdemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mdemo.mak" CFG="Mdemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mdemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Mdemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Mdemo - Win32 Debug"
CPP=cl.exe
F90=fl32.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Mdemo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Mdemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\Abs_phas.obj"
	-@erase "$(INTDIR)\Datagen.obj"
	-@erase "$(INTDIR)\Dbsetup.obj"
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\fft.obj"
	-@erase "$(INTDIR)\Fft_scr.obj"
	-@erase "$(INTDIR)\Guisetup.obj"
	-@erase "$(INTDIR)\Lpfilter.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Plotter.obj"
	-@erase "$(INTDIR)\Splitter.obj"
	-@erase "$(INTDIR)\System.obj"
	-@erase ".\Mdemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo
# ADD F90 /Ox /I "Release/" /c /nologo
F90_PROJ=/Ox /I "Release/" /c /nologo /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "." /I "./include" /I "./scripts" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "." /I "./include" /I "./scripts" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/Mdemo.pch" /YX /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mdemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /machine:I386 /out:"Mdemo.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Mdemo.pdb" /machine:I386 /out:"Mdemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Abs_phas.obj" \
	"$(INTDIR)\Datagen.obj" \
	"$(INTDIR)\Dbsetup.obj" \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\fft.obj" \
	"$(INTDIR)\Fft_scr.obj" \
	"$(INTDIR)\Guisetup.obj" \
	"$(INTDIR)\Lpfilter.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Plotter.obj" \
	"$(INTDIR)\Splitter.obj" \
	"$(INTDIR)\System.obj" \
	".\lib\gplotw32.lib" \
	".\lib\gui20w32.lib" \
	".\lib\mgk60.lib" \
	".\lib\simuiw32.lib"

".\Mdemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Mdemo_d.exe"

CLEAN : 
	-@erase "$(INTDIR)\Abs_phas.obj"
	-@erase "$(INTDIR)\Datagen.obj"
	-@erase "$(INTDIR)\Dbsetup.obj"
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\fft.obj"
	-@erase "$(INTDIR)\Fft_scr.obj"
	-@erase "$(INTDIR)\Guisetup.obj"
	-@erase "$(INTDIR)\Lpfilter.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\Plotter.obj"
	-@erase "$(INTDIR)\Splitter.obj"
	-@erase "$(INTDIR)\System.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Mdemo_d.pdb"
	-@erase ".\Mdemo_d.exe"
	-@erase ".\Mdemo_d.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo
# ADD F90 /Zi /I "Debug/" /c /nologo
F90_PROJ=/Zi /I "Debug/" /c /nologo /Fo"Debug/" /Fd"Debug/Mdemo.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "." /I "./include" /I "./scripts" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "." /I "./include" /I "./scripts"\
 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/Mdemo.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mdemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Mdemo_d.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Mdemo_d.pdb" /debug /machine:I386\
 /out:"Mdemo_d.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Abs_phas.obj" \
	"$(INTDIR)\Datagen.obj" \
	"$(INTDIR)\Dbsetup.obj" \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\fft.obj" \
	"$(INTDIR)\Fft_scr.obj" \
	"$(INTDIR)\Guisetup.obj" \
	"$(INTDIR)\Lpfilter.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\Plotter.obj" \
	"$(INTDIR)\Splitter.obj" \
	"$(INTDIR)\System.obj" \
	".\lib\gplotw32.lib" \
	".\lib\gui20w32.lib" \
	".\lib\mgk60_d.lib" \
	".\lib\simuiw32_d.lib"

".\Mdemo_d.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "Mdemo - Win32 Release"
# Name "Mdemo - Win32 Debug"

!IF  "$(CFG)" == "Mdemo - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\System.c
DEP_CPP_SYSTE=\
	".\./include\mgk60.h"\
	".\System.h"\
	

"$(INTDIR)\System.obj" : $(SOURCE) $(DEP_CPP_SYSTE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\main.c
DEP_CPP_MAIN_=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\System.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lib\gplotw32.lib

!IF  "$(CFG)" == "Mdemo - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lib\gui20w32.lib

!IF  "$(CFG)" == "Mdemo - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lib\mgk60.lib

!IF  "$(CFG)" == "Mdemo - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lib\mgk60_d.lib

!IF  "$(CFG)" == "Mdemo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lib\simuiw32.lib

!IF  "$(CFG)" == "Mdemo - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lib\simuiw32_d.lib

!IF  "$(CFG)" == "Mdemo - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Mdemo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fft.c
DEP_CPP_FFT_C=\
	".\./include\mgk60.h"\
	".\fft.h"\
	

"$(INTDIR)\fft.obj" : $(SOURCE) $(DEP_CPP_FFT_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Splitter.c
DEP_CPP_SPLIT=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Splitter.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Datagen.c
DEP_CPP_DATAG=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Datagen.obj" : $(SOURCE) $(DEP_CPP_DATAG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Dbsetup.c
DEP_CPP_DBSET=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Dbsetup.obj" : $(SOURCE) $(DEP_CPP_DBSET) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Envelope.c
DEP_CPP_ENVEL=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Envelope.obj" : $(SOURCE) $(DEP_CPP_ENVEL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Fft_scr.c
DEP_CPP_FFT_S=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Fft_scr.obj" : $(SOURCE) $(DEP_CPP_FFT_S) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Guisetup.c
DEP_CPP_GUISE=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Guisetup.obj" : $(SOURCE) $(DEP_CPP_GUISE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Lpfilter.c
DEP_CPP_LPFIL=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Lpfilter.obj" : $(SOURCE) $(DEP_CPP_LPFIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Plotter.c
DEP_CPP_PLOTT=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Plotter.obj" : $(SOURCE) $(DEP_CPP_PLOTT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\scripts\Abs_phas.c
DEP_CPP_ABS_P=\
	".\./include\mgk60.h"\
	".\./include\simgui.h"\
	".\fft.h"\
	".\scripts\scripts.h"\
	".\System.h"\
	

"$(INTDIR)\Abs_phas.obj" : $(SOURCE) $(DEP_CPP_ABS_P) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
