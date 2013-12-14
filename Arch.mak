# Microsoft Developer Studio Generated NMAKE File, Based on Arch.dsp
!IF "$(CFG)" == ""
CFG=Arch - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Arch - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Arch - Win32 Release" && "$(CFG)" != "Arch - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Arch.mak" CFG="Arch - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Arch - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Arch - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Arch - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Arch.exe"


CLEAN :
	-@erase "$(INTDIR)\Arch.obj"
	-@erase "$(INTDIR)\Arch.pch"
	-@erase "$(INTDIR)\Arch.res"
	-@erase "$(INTDIR)\ArchDoc.obj"
	-@erase "$(INTDIR)\ArchGL.obj"
	-@erase "$(INTDIR)\ArchView.obj"
	-@erase "$(INTDIR)\Building.obj"
	-@erase "$(INTDIR)\CurvedWall.obj"
	-@erase "$(INTDIR)\Door.obj"
	-@erase "$(INTDIR)\Element.obj"
	-@erase "$(INTDIR)\Fixture.obj"
	-@erase "$(INTDIR)\FixtureDialog.obj"
	-@erase "$(INTDIR)\Floor.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Pillar.obj"
	-@erase "$(INTDIR)\PillarProp.obj"
	-@erase "$(INTDIR)\Plane.obj"
	-@erase "$(INTDIR)\Stairs.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vfd.obj"
	-@erase "$(INTDIR)\Wall.obj"
	-@erase "$(OUTDIR)\Arch.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Arch.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Arch.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Arch.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Arch.pdb" /machine:I386 /out:"$(OUTDIR)\Arch.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Arch.obj" \
	"$(INTDIR)\ArchDoc.obj" \
	"$(INTDIR)\ArchGL.obj" \
	"$(INTDIR)\ArchView.obj" \
	"$(INTDIR)\Building.obj" \
	"$(INTDIR)\CurvedWall.obj" \
	"$(INTDIR)\Door.obj" \
	"$(INTDIR)\Element.obj" \
	"$(INTDIR)\Fixture.obj" \
	"$(INTDIR)\FixtureDialog.obj" \
	"$(INTDIR)\Floor.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Pillar.obj" \
	"$(INTDIR)\PillarProp.obj" \
	"$(INTDIR)\Plane.obj" \
	"$(INTDIR)\Stairs.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vfd.obj" \
	"$(INTDIR)\Wall.obj" \
	"$(INTDIR)\Arch.res"

"$(OUTDIR)\Arch.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Arch.exe" "$(OUTDIR)\Arch.bsc"


CLEAN :
	-@erase "$(INTDIR)\Arch.obj"
	-@erase "$(INTDIR)\Arch.pch"
	-@erase "$(INTDIR)\Arch.res"
	-@erase "$(INTDIR)\Arch.sbr"
	-@erase "$(INTDIR)\ArchDoc.obj"
	-@erase "$(INTDIR)\ArchDoc.sbr"
	-@erase "$(INTDIR)\ArchGL.obj"
	-@erase "$(INTDIR)\ArchGL.sbr"
	-@erase "$(INTDIR)\ArchView.obj"
	-@erase "$(INTDIR)\ArchView.sbr"
	-@erase "$(INTDIR)\Building.obj"
	-@erase "$(INTDIR)\Building.sbr"
	-@erase "$(INTDIR)\CurvedWall.obj"
	-@erase "$(INTDIR)\CurvedWall.sbr"
	-@erase "$(INTDIR)\Door.obj"
	-@erase "$(INTDIR)\Door.sbr"
	-@erase "$(INTDIR)\Element.obj"
	-@erase "$(INTDIR)\Element.sbr"
	-@erase "$(INTDIR)\Fixture.obj"
	-@erase "$(INTDIR)\Fixture.sbr"
	-@erase "$(INTDIR)\FixtureDialog.obj"
	-@erase "$(INTDIR)\FixtureDialog.sbr"
	-@erase "$(INTDIR)\Floor.obj"
	-@erase "$(INTDIR)\Floor.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Pillar.obj"
	-@erase "$(INTDIR)\Pillar.sbr"
	-@erase "$(INTDIR)\PillarProp.obj"
	-@erase "$(INTDIR)\PillarProp.sbr"
	-@erase "$(INTDIR)\Plane.obj"
	-@erase "$(INTDIR)\Plane.sbr"
	-@erase "$(INTDIR)\Stairs.obj"
	-@erase "$(INTDIR)\Stairs.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vfd.obj"
	-@erase "$(INTDIR)\vfd.sbr"
	-@erase "$(INTDIR)\Wall.obj"
	-@erase "$(INTDIR)\Wall.sbr"
	-@erase "$(OUTDIR)\Arch.bsc"
	-@erase "$(OUTDIR)\Arch.exe"
	-@erase "$(OUTDIR)\Arch.ilk"
	-@erase "$(OUTDIR)\Arch.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Arch.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Arch.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Arch.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Arch.sbr" \
	"$(INTDIR)\ArchDoc.sbr" \
	"$(INTDIR)\ArchGL.sbr" \
	"$(INTDIR)\ArchView.sbr" \
	"$(INTDIR)\Building.sbr" \
	"$(INTDIR)\CurvedWall.sbr" \
	"$(INTDIR)\Door.sbr" \
	"$(INTDIR)\Element.sbr" \
	"$(INTDIR)\Fixture.sbr" \
	"$(INTDIR)\FixtureDialog.sbr" \
	"$(INTDIR)\Floor.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Pillar.sbr" \
	"$(INTDIR)\PillarProp.sbr" \
	"$(INTDIR)\Plane.sbr" \
	"$(INTDIR)\Stairs.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vfd.sbr" \
	"$(INTDIR)\Wall.sbr"

"$(OUTDIR)\Arch.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Arch.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Arch.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Arch.obj" \
	"$(INTDIR)\ArchDoc.obj" \
	"$(INTDIR)\ArchGL.obj" \
	"$(INTDIR)\ArchView.obj" \
	"$(INTDIR)\Building.obj" \
	"$(INTDIR)\CurvedWall.obj" \
	"$(INTDIR)\Door.obj" \
	"$(INTDIR)\Element.obj" \
	"$(INTDIR)\Fixture.obj" \
	"$(INTDIR)\FixtureDialog.obj" \
	"$(INTDIR)\Floor.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Pillar.obj" \
	"$(INTDIR)\PillarProp.obj" \
	"$(INTDIR)\Plane.obj" \
	"$(INTDIR)\Stairs.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vfd.obj" \
	"$(INTDIR)\Wall.obj" \
	"$(INTDIR)\Arch.res"

"$(OUTDIR)\Arch.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Arch.dep")
!INCLUDE "Arch.dep"
!ELSE 
!MESSAGE Warning: cannot find "Arch.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Arch - Win32 Release" || "$(CFG)" == "Arch - Win32 Debug"
SOURCE=.\Arch.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Arch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Arch.obj"	"$(INTDIR)\Arch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\Arch.rc

"$(INTDIR)\Arch.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ArchDoc.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\ArchDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\ArchDoc.obj"	"$(INTDIR)\ArchDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\ArchGL.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\ArchGL.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\ArchGL.obj"	"$(INTDIR)\ArchGL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\ArchView.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\ArchView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\ArchView.obj"	"$(INTDIR)\ArchView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\Build\Building.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Building.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Building.obj"	"$(INTDIR)\Building.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Build\CurvedWall.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\CurvedWall.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\CurvedWall.obj"	"$(INTDIR)\CurvedWall.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Build\Door.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Door.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Door.obj"	"$(INTDIR)\Door.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Build\Element.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Element.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Element.obj"	"$(INTDIR)\Element.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Build\Fixture.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Fixture.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Fixture.obj"	"$(INTDIR)\Fixture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\FixtureDialog.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\FixtureDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\FixtureDialog.obj"	"$(INTDIR)\FixtureDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\Build\Floor.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Floor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Floor.obj"	"$(INTDIR)\Floor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\Build\Pillar.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Pillar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Pillar.obj"	"$(INTDIR)\Pillar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\PillarProp.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\PillarProp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\PillarProp.obj"	"$(INTDIR)\PillarProp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\Build\Plane.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Plane.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Plane.obj"	"$(INTDIR)\Plane.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Build\Stairs.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Stairs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Stairs.obj"	"$(INTDIR)\Stairs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Arch.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Arch.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Arch.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Arch.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\vfd.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\vfd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\vfd.obj"	"$(INTDIR)\vfd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"


!ENDIF 

SOURCE=.\Build\Wall.cpp

!IF  "$(CFG)" == "Arch - Win32 Release"


"$(INTDIR)\Wall.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"


"$(INTDIR)\Wall.obj"	"$(INTDIR)\Wall.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Arch.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

