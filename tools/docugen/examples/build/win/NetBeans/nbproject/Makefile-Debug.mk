#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=C:/MinGW/bin/gcc.exe
CCC=C:/MinGW/bin/g++.exe
CXX=C:/MinGW/bin/g++.exe
FC=gfortran.exe
AS=C:\MinGW\bin\as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
<zeriph_inline_source>/	${OBJECTDIR}/_ext/2002356267/{0.nm}.o \</zeriph_inline_source>

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a

<start_zeriph_omni_section>
<zeriph_source_format>${OBJECTDIR}/_ext/2002356267/{0.nm}.o: {0}
	${MKDIR} -p ${OBJECTDIR}/_ext/2002356267
	$(COMPILE.cc) -g -I/source/omni -std=c++98 -o ${OBJECTDIR}/_ext/2002356267/{0.nm}.o {0}

</zeriph_source_format>
<zeriph_header_format>SOURCE_ONLY</zeriph_header_format>
<zeriph_slash>/</zeriph_slash>
<zeriph_path>/C/source/omni/</zeriph_path>
<zeriph_tabspace></zeriph_tabspace>
<zeriph_virt_folder></zeriph_virt_folder>
<zeriph_virt_folder_rec>false</zeriph_virt_folder_rec>
</start_zeriph_omni_section>

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetbeans.a

# Subprojects
.clean-subprojects:
