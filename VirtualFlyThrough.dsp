# Microsoft Developer Studio Project File - Name="VirtualFlyThrough" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=VirtualFlyThrough - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VirtualFlyThrough.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VirtualFlyThrough.mak" CFG="VirtualFlyThrough - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VirtualFlyThrough - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "VirtualFlyThrough - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VirtualFlyThrough - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /nodefaultlib:"libcd.lib"

!ELSEIF  "$(CFG)" == "VirtualFlyThrough - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x40d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VirtualFlyThrough - Win32 Release"
# Name "VirtualFlyThrough - Win32 Debug"
# Begin Group "Library"

# PROP Default_Filter ""
# Begin Group "GenericClasses"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Library\GenericClasses\Device.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GenericClasses\Device.h
# End Source File
# Begin Source File

SOURCE=.\Library\GenericClasses\List.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GenericClasses\List.h
# End Source File
# End Group
# Begin Group "GraphicElements"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Library\GraphicElements\IndexList.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\IndexList.h
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\InterList.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\InterList.h
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\Point.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\Point.h
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\Polygon.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\Polygon.h
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\Polyhedron.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicElements\Polyhedron.h
# End Source File
# End Group
# Begin Group "GraphicManagers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Library\GraphicManagers\RenderMngr.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicManagers\RenderMngr.h
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicManagers\TranslateMngr.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\GraphicManagers\TranslateMngr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Library\VirtualFlyThrough.cpp
# End Source File
# Begin Source File

SOURCE=.\Library\VirtualFlyThrough.h
# End Source File
# End Group
# Begin Group "LibUser"

# PROP Default_Filter ""
# Begin Group "GenericUtilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LibUser\GenericUtilities\Directory.cpp
# End Source File
# Begin Source File

SOURCE=.\LibUser\GenericUtilities\Directory.h
# End Source File
# End Group
# Begin Group "GraphicHandlers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LibUser\GraphicHandlers\GluiMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicHandlers\GluiMenu.h
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicHandlers\GlutDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicHandlers\GlutDevice.h
# End Source File
# End Group
# Begin Group "GraphicInputFiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\1701.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Asteroid.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Cube.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Diamond.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Dyna.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Glass1.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Intro.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Oct2Stel.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Pyramid.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Scene.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Shuttle.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Star.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Tank.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Two.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Vase.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\Warbird.plg
# End Source File
# Begin Source File

SOURCE=.\LibUser\GraphicInputFiles\X29A.plg
# End Source File
# End Group
# Begin Source File

SOURCE=.\LibUser\MainInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\LibUser\MainInterface.h
# End Source File
# End Group
# End Target
# End Project
