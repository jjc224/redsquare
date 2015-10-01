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
CND_CONF=Release
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
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

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
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/CompressUtils.o ../FileArchiver/CompressUtils.cpp

${OBJECTDIR}/_ext/583062117/DBConnector.o: ../FileArchiver/DBConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/DBConnector.o ../FileArchiver/DBConnector.cpp

${OBJECTDIR}/_ext/583062117/FileArchiver.o: ../FileArchiver/FileArchiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileArchiver.o ../FileArchiver/FileArchiver.cpp

${OBJECTDIR}/_ext/583062117/FileLib.o: ../FileArchiver/FileLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileLib.o ../FileArchiver/FileLib.cpp

${OBJECTDIR}/_ext/583062117/FileRecord.o: ../FileArchiver/FileRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileRecord.o ../FileArchiver/FileRecord.cpp

${OBJECTDIR}/_ext/583062117/MurmurHash3.o: ../FileArchiver/MurmurHash3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/MurmurHash3.o ../FileArchiver/MurmurHash3.cpp

${OBJECTDIR}/_ext/583062117/TestUtilities.o: ../FileArchiver/TestUtilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/TestUtilities.o ../FileArchiver/TestUtilities.cpp

${OBJECTDIR}/_ext/583062117/Utilities.o: ../FileArchiver/Utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/Utilities.o ../FileArchiver/Utilities.cpp

${OBJECTDIR}/_ext/583062117/VersionRecord.o: ../FileArchiver/VersionRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/VersionRecord.o ../FileArchiver/VersionRecord.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/backendtestrunner.o ${TESTDIR}/tests/backendtests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/FileLibTester.o ${TESTDIR}/FileLibTesterRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/tests/backendtestrunner.o: tests/backendtestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/backendtestrunner.o tests/backendtestrunner.cpp


${TESTDIR}/tests/backendtests.o: tests/backendtests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/backendtests.o tests/backendtests.cpp


${TESTDIR}/tests/FileLibTester.o: tests/FileLibTester.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/FileLibTester.o tests/FileLibTester.cpp


${TESTDIR}/FileLibTesterRunner.o: FileLibTesterRunner.cpp 
	${MKDIR} -p ${TESTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../FileArchiver/ `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/FileLibTesterRunner.o FileLibTesterRunner.cpp


${OBJECTDIR}/_ext/583062117/CompressUtils_nomain.o: ${OBJECTDIR}/_ext/583062117/CompressUtils.o ../FileArchiver/CompressUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/CompressUtils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/CompressUtils_nomain.o ../FileArchiver/CompressUtils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/CompressUtils.o ${OBJECTDIR}/_ext/583062117/CompressUtils_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/DBConnector_nomain.o: ${OBJECTDIR}/_ext/583062117/DBConnector.o ../FileArchiver/DBConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/DBConnector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/DBConnector_nomain.o ../FileArchiver/DBConnector.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/DBConnector.o ${OBJECTDIR}/_ext/583062117/DBConnector_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/FileArchiver_nomain.o: ${OBJECTDIR}/_ext/583062117/FileArchiver.o ../FileArchiver/FileArchiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/FileArchiver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileArchiver_nomain.o ../FileArchiver/FileArchiver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/FileArchiver.o ${OBJECTDIR}/_ext/583062117/FileArchiver_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/FileLib_nomain.o: ${OBJECTDIR}/_ext/583062117/FileLib.o ../FileArchiver/FileLib.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/FileLib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileLib_nomain.o ../FileArchiver/FileLib.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/FileLib.o ${OBJECTDIR}/_ext/583062117/FileLib_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/FileRecord_nomain.o: ${OBJECTDIR}/_ext/583062117/FileRecord.o ../FileArchiver/FileRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/FileRecord.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/FileRecord_nomain.o ../FileArchiver/FileRecord.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/FileRecord.o ${OBJECTDIR}/_ext/583062117/FileRecord_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/MurmurHash3_nomain.o: ${OBJECTDIR}/_ext/583062117/MurmurHash3.o ../FileArchiver/MurmurHash3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/MurmurHash3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/MurmurHash3_nomain.o ../FileArchiver/MurmurHash3.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/MurmurHash3.o ${OBJECTDIR}/_ext/583062117/MurmurHash3_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/TestUtilities_nomain.o: ${OBJECTDIR}/_ext/583062117/TestUtilities.o ../FileArchiver/TestUtilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/TestUtilities.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/TestUtilities_nomain.o ../FileArchiver/TestUtilities.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/TestUtilities.o ${OBJECTDIR}/_ext/583062117/TestUtilities_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/Utilities_nomain.o: ${OBJECTDIR}/_ext/583062117/Utilities.o ../FileArchiver/Utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/Utilities.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/Utilities_nomain.o ../FileArchiver/Utilities.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/Utilities.o ${OBJECTDIR}/_ext/583062117/Utilities_nomain.o;\
	fi

${OBJECTDIR}/_ext/583062117/VersionRecord_nomain.o: ${OBJECTDIR}/_ext/583062117/VersionRecord.o ../FileArchiver/VersionRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/583062117
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/583062117/VersionRecord.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/583062117/VersionRecord_nomain.o ../FileArchiver/VersionRecord.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/583062117/VersionRecord.o ${OBJECTDIR}/_ext/583062117/VersionRecord_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../FileArchiver/ -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/filearchiverunittests

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
