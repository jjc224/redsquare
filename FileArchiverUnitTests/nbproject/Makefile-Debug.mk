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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/583062117/CompressUtils.o \
	${OBJECTDIR}/_ext/583062117/DBConnector.o \
	${OBJECTDIR}/_ext/583062117/FileArchiver.o \
	${OBJECTDIR}/_ext/583062117/FileLib.o \
	${OBJECTDIR}/_ext/583062117/FileRecord.o \
	${OBJECTDIR}/_ext/583062117/MurmurHash3.o \
	${OBJECTDIR}/_ext/583062117/TestUtilities.o \
	${OBJECTDIR}/_ext/583062117/Utilities.o \
	${OBJECTDIR}/_ext/583062117/VersionRecord.o \
	${OBJECTDIR}/_ext/583062117/main.o


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
LDLIBSOPTIONS=-lmysqlcppconn -lboost_system -lboost_filesystem -lboost_regex

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiverunittests

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiverunittests: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiverunittests ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/583062117/CompressUtils.o: ../FileArchiver/CompressUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/CompressUtils.o ../FileArchiver/CompressUtils.cpp

${OBJECTDIR}/_ext/583062117/DBConnector.o: ../FileArchiver/DBConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/DBConnector.o ../FileArchiver/DBConnector.cpp

${OBJECTDIR}/_ext/583062117/FileArchiver.o: ../FileArchiver/FileArchiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileArchiver.o ../FileArchiver/FileArchiver.cpp

${OBJECTDIR}/_ext/583062117/FileLib.o: ../FileArchiver/FileLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileLib.o ../FileArchiver/FileLib.cpp

${OBJECTDIR}/_ext/583062117/FileRecord.o: ../FileArchiver/FileRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileRecord.o ../FileArchiver/FileRecord.cpp

${OBJECTDIR}/_ext/583062117/MurmurHash3.o: ../FileArchiver/MurmurHash3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/MurmurHash3.o ../FileArchiver/MurmurHash3.cpp

${OBJECTDIR}/_ext/583062117/TestUtilities.o: ../FileArchiver/TestUtilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/TestUtilities.o ../FileArchiver/TestUtilities.cpp

${OBJECTDIR}/_ext/583062117/Utilities.o: ../FileArchiver/Utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/Utilities.o ../FileArchiver/Utilities.cpp

${OBJECTDIR}/_ext/583062117/VersionRecord.o: ../FileArchiver/VersionRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/VersionRecord.o ../FileArchiver/VersionRecord.cpp

${OBJECTDIR}/_ext/583062117/main.o: ../FileArchiver/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/main.o ../FileArchiver/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiverunittests

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
