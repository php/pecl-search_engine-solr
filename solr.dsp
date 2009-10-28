# Microsoft Developer Studio Project File - Name="Solr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# $Id$
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Solr - Win32 Debug_TS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Solr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Solr.mak" CFG="Solr - Win32 Debug_TS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Solr - Win32 Release_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Solr - Win32 Debug_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Solr - Win32 Release_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_TS"
# PROP BASE Intermediate_Dir "Release_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_TS"
# PROP Intermediate_Dir "Release_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SOLR_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\.." /I "..\..\Zend" /I "..\..\TSRM" /I "..\..\main" /D "WIN32" /D "PHP_EXPORTS" /D "COMPILE_DL_SOLR" /D ZTS=1 /D HAVE_SOLR=1  /D ZEND_DEBUG=0 /D "NDEBUG" /D "_WINDOWS" /D "ZEND_WIN32" /D "PHP_WIN32" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib php5ts.lib /nologo /dll /machine:I386
# ADD LINK32 wsock32.lib php5ts.lib libcurl.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /machine:I386 /out:"..\..\Release_TS/php_solr.dll" /implib:"..\..\Release_TS/php_solr.lib" /libpath:"..\..\Release_TS" /libpath:"..\..\Release_TS_Inline" /libpath:"..\..\..\bindlib_w32\Release"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Solr - Win32 Debug_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_TS"
# PROP BASE Intermediate_Dir "Debug_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_TS"
# PROP Intermediate_Dir "Debug_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SOLR_EXPORTS" /YX /FD /GZ  /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\Zend" /I "..\..\TSRM" /I "..\..\main" /D ZEND_DEBUG=1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "PHP_EXPORTS" /D "COMPILE_DL_SOLR" /D ZTS=1 /D "ZEND_WIN32" /D "PHP_WIN32" /D HAVE_SOLR=1  /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib php5ts.lib /nologo /dll /machine:I386
# ADD LINK32 php5ts_debug.lib libcurl.lib ws2_32.lib resolv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /debug /machine:I386 /nodefaultlib:"msvcrt" /out:"..\..\Debug_TS\php_solr.dll" /implib:"..\..\Debug_TS/php_solr.lib" /libpath:"..\..\Debug_TS" /libpath:"..\..\..\bindlib_w32\Release"

!ENDIF 

# Begin Target

# Name "Solr - Win32 Release_TS"
# Name "Solr - Win32 Debug_TS"

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Source File

SOURCE=./php_solr.c
# End Source File

# Begin Source File

SOURCE=./php_solr_exception.c
# End Source File

# Begin Source File

SOURCE=./php_solr_object.c
# End Source File

# Begin Source File

SOURCE=./php_solr_response.c
# End Source File

# Begin Source File

SOURCE=./php_solr_document.c
# End Source File

# Begin Source File

SOURCE=./php_solr_input_document.c
# End Source File

# Begin Source File

SOURCE=./php_solr_query.c
# End Source File

# Begin Source File

SOURCE=./php_solr_client.c
# End Source File

# Begin Source File

SOURCE=./php_solr_functions.c
# End Source File

# Begin Source File

SOURCE=./php_solr_params.c
# End Source File

# Begin Source File

SOURCE=./php_solr_utils.c
# End Source File

# Begin Source File

SOURCE=./solr_functions_debug.c
# End Source File

# Begin Source File

SOURCE=./solr_functions_params.c
# End Source File

# Begin Source File

SOURCE=./solr_functions_document.c
# End Source File

# Begin Source File

SOURCE=./solr_functions_response.c
# End Source File

# Begin Source File

SOURCE=./solr_functions_client.c
# End Source File

# Begin Source File

SOURCE=./solr_functions_helpers.c
# End Source File

# Begin Source File

SOURCE=./solr_string.c
# End Source File

# End Group

# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"

# Begin Source File

SOURCE=.\php_solr.h
# End Source File

# Begin Source File

SOURCE=.\php_solr_api.h
# End Source File

# Begin Source File

SOURCE=.\solr_constants.h
# End Source File

# Begin Source File

SOURCE=.\solr_macros.h
# End Source File

# Begin Source File

SOURCE=.\solr_string.h
# End Source File

# Begin Source File

SOURCE=.\solr_types.h
# End Source File
# End Group
# End Target
# End Project
