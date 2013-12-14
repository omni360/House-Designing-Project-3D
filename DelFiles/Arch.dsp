# Microsoft Developer Studio Project File - Name="Arch" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Arch - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Arch.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Arch - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Arch - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Arch - Win32 Release"
# Name "Arch - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Arch.cpp
# End Source File
# Begin Source File

SOURCE=.\Arch.rc
# End Source File
# Begin Source File

SOURCE=.\ArchDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchGL.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchView.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Building.cpp
# End Source File
# Begin Source File

SOURCE=.\GL3D\Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\Ceiling.cpp
# End Source File
# Begin Source File

SOURCE=.\Ceilingdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\chair_type.cpp
# End Source File
# Begin Source File

SOURCE=.\ChairObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\CurvedWall.cpp
# End Source File
# Begin Source File

SOURCE=.\CurvedWallDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Door.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Element.cpp
# End Source File
# Begin Source File

SOURCE=.\EnBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Fixture.cpp
# End Source File
# Begin Source File

SOURCE=.\FixtureDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FixtureWall.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Floor.cpp
# End Source File
# Begin Source File

SOURCE=.\GL3dView.cpp
# End Source File
# Begin Source File

SOURCE=.\Load3DS.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectMoveDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjRotateDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Pillar.cpp
# End Source File
# Begin Source File

SOURCE=.\pillardlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Plane.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleWall.cpp
# End Source File
# Begin Source File

SOURCE=.\Sofadlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Sofaobject.cpp
# End Source File
# Begin Source File

SOURCE=.\sofatype.cpp
# End Source File
# Begin Source File

SOURCE=.\SpiralDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Spiralstair.cpp
# End Source File
# Begin Source File

SOURCE=.\Sport.cpp
# End Source File
# Begin Source File

SOURCE=.\StairDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Stairs.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StraightWallDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Tabledlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Tableobject.cpp
# End Source File
# Begin Source File

SOURCE=.\GL3D\Vector3.cpp
# End Source File
# Begin Source File

SOURCE=.\vfd.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Wall.cpp
# End Source File
# Begin Source File

SOURCE=.\Build\Wind.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Arch.h
# End Source File
# Begin Source File

SOURCE=.\Build\ArchCons.h
# End Source File
# Begin Source File

SOURCE=.\ArchDoc.h
# End Source File
# Begin Source File

SOURCE=.\Archdraw.h
# End Source File
# Begin Source File

SOURCE=.\ArchGL.h
# End Source File
# Begin Source File

SOURCE=.\ArchView.h
# End Source File
# Begin Source File

SOURCE=.\Build\Building.h
# End Source File
# Begin Source File

SOURCE=.\GL3D\Camera.h
# End Source File
# Begin Source File

SOURCE=.\Ceiling.h
# End Source File
# Begin Source File

SOURCE=.\Ceilingdlg.h
# End Source File
# Begin Source File

SOURCE=.\chair_type.h
# End Source File
# Begin Source File

SOURCE=.\ChairObject.h
# End Source File
# Begin Source File

SOURCE=.\Build\CurvedWall.h
# End Source File
# Begin Source File

SOURCE=.\CurvedWallDlg.h
# End Source File
# Begin Source File

SOURCE=.\Build\Door.h
# End Source File
# Begin Source File

SOURCE=.\Build\Element.h
# End Source File
# Begin Source File

SOURCE=.\EnBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Build\Fixture.h
# End Source File
# Begin Source File

SOURCE=.\FixtureDialog.h
# End Source File
# Begin Source File

SOURCE=.\FixtureWall.h
# End Source File
# Begin Source File

SOURCE=.\Build\Floor.h
# End Source File
# Begin Source File

SOURCE=.\GL3dView.h
# End Source File
# Begin Source File

SOURCE=.\GL3D\glprocs.h
# End Source File
# Begin Source File

SOURCE=.\Load3DS.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ObjectMoveDLG.h
# End Source File
# Begin Source File

SOURCE=.\ObjRotateDLG.h
# End Source File
# Begin Source File

SOURCE=.\Build\Pillar.h
# End Source File
# Begin Source File

SOURCE=.\pillardlg.h
# End Source File
# Begin Source File

SOURCE=.\Build\Plane.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SimpleWall.h
# End Source File
# Begin Source File

SOURCE=.\Sofadlg.h
# End Source File
# Begin Source File

SOURCE=.\Sofaobject.h
# End Source File
# Begin Source File

SOURCE=.\sofatype.h
# End Source File
# Begin Source File

SOURCE=.\SpiralDlg.h
# End Source File
# Begin Source File

SOURCE=.\Spiralstair.h
# End Source File
# Begin Source File

SOURCE=.\Sport.h
# End Source File
# Begin Source File

SOURCE=.\StairDlg.h
# End Source File
# Begin Source File

SOURCE=.\Build\Stairs.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StraightWallDlg.h
# End Source File
# Begin Source File

SOURCE=.\Tabledlg.h
# End Source File
# Begin Source File

SOURCE=.\Tableobject.h
# End Source File
# Begin Source File

SOURCE=.\Tex.h
# End Source File
# Begin Source File

SOURCE=.\GL3D\Vector3.h
# End Source File
# Begin Source File

SOURCE=.\vfd.h
# End Source File
# Begin Source File

SOURCE=.\Build\Wall.h
# End Source File
# Begin Source File

SOURCE=.\Build\Wind.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Arch.ico
# End Source File
# Begin Source File

SOURCE=.\res\Arch.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ArchDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\grass.bmp
# End Source File
# Begin Source File

SOURCE=.\res\harrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\hcross.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Arch.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
