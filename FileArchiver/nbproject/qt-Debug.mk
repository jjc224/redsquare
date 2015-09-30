#############################################################################
# Makefile for building: dist/Debug/GNU-Linux-x86/FileArchiver
# Generated by qmake (2.01a) (Qt 4.8.2) on: Wed Sep 30 11:59:31 2015
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: /usr/bin/qmake VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -Inbproject -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lmysqlcppconn -lboost_system -lboost_filesystem -lboost_regex -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux-x86/

####### Files

SOURCES       = CompressUtils.cpp \
		DBConnector.cpp \
		FileArchiver.cpp \
		FileLib.cpp \
		FileRecord.cpp \
		GetCommentForm.cpp \
		MurmurHash3.cpp \
		MyWindow.cpp \
		RetrieveForm.cpp \
		TableModel.cpp \
		TestUtilities.cpp \
		Utilities.cpp \
		VersionRecord.cpp \
		main.cpp moc_GetCommentForm.cpp \
		moc_MyWindow.cpp \
		moc_RetrieveForm.cpp \
		moc_TableModel.cpp
OBJECTS       = build/Debug/GNU-Linux-x86/CompressUtils.o \
		build/Debug/GNU-Linux-x86/DBConnector.o \
		build/Debug/GNU-Linux-x86/FileArchiver.o \
		build/Debug/GNU-Linux-x86/FileLib.o \
		build/Debug/GNU-Linux-x86/FileRecord.o \
		build/Debug/GNU-Linux-x86/GetCommentForm.o \
		build/Debug/GNU-Linux-x86/MurmurHash3.o \
		build/Debug/GNU-Linux-x86/MyWindow.o \
		build/Debug/GNU-Linux-x86/RetrieveForm.o \
		build/Debug/GNU-Linux-x86/TableModel.o \
		build/Debug/GNU-Linux-x86/TestUtilities.o \
		build/Debug/GNU-Linux-x86/Utilities.o \
		build/Debug/GNU-Linux-x86/VersionRecord.o \
		build/Debug/GNU-Linux-x86/main.o \
		build/Debug/GNU-Linux-x86/moc_GetCommentForm.o \
		build/Debug/GNU-Linux-x86/moc_MyWindow.o \
		build/Debug/GNU-Linux-x86/moc_RetrieveForm.o \
		build/Debug/GNU-Linux-x86/moc_TableModel.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		nbproject/qt-Debug.pro
QMAKE_TARGET  = FileArchiver
DESTDIR       = dist/Debug/GNU-Linux-x86/
TARGET        = dist/Debug/GNU-Linux-x86/FileArchiver

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Debug.mk $(TARGET)

$(TARGET): ui_GetCommentForm.h ui_MyWindow.h ui_RetrieveForm.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dist/Debug/GNU-Linux-x86/ || $(MKDIR) dist/Debug/GNU-Linux-x86/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

qttmp-Debug.mk: nbproject/qt-Debug.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist: 
	@$(CHK_DIR_EXISTS) build/Debug/GNU-Linux-x86/FileArchiver1.0.0 || $(MKDIR) build/Debug/GNU-Linux-x86/FileArchiver1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/Debug/GNU-Linux-x86/FileArchiver1.0.0/ && $(COPY_FILE) --parents CompressUtils.h DBConnector.h FileArchiver.h FileLib.h FileRecord.h GetCommentForm.h MurmurHash3.h MyWindow.h ProjectConstants.h RetrieveForm.h TableModel.h TestUtilities.h VersionRecord.h build/Debug/GNU-Linux-x86/FileArchiver1.0.0/ && $(COPY_FILE) --parents CompressUtils.cpp DBConnector.cpp FileArchiver.cpp FileLib.cpp FileRecord.cpp GetCommentForm.cpp MurmurHash3.cpp MyWindow.cpp RetrieveForm.cpp TableModel.cpp TestUtilities.cpp Utilities.cpp VersionRecord.cpp main.cpp build/Debug/GNU-Linux-x86/FileArchiver1.0.0/ && $(COPY_FILE) --parents GetCommentForm.ui MyWindow.ui RetrieveForm.ui build/Debug/GNU-Linux-x86/FileArchiver1.0.0/ && (cd `dirname build/Debug/GNU-Linux-x86/FileArchiver1.0.0` && $(TAR) FileArchiver1.0.0.tar FileArchiver1.0.0 && $(COMPRESS) FileArchiver1.0.0.tar) && $(MOVE) `dirname build/Debug/GNU-Linux-x86/FileArchiver1.0.0`/FileArchiver1.0.0.tar.gz . && $(DEL_FILE) -r build/Debug/GNU-Linux-x86/FileArchiver1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) qttmp-Debug.mk


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_GetCommentForm.cpp moc_MyWindow.cpp moc_RetrieveForm.cpp moc_TableModel.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_GetCommentForm.cpp moc_MyWindow.cpp moc_RetrieveForm.cpp moc_TableModel.cpp
moc_GetCommentForm.cpp: ui_GetCommentForm.h \
		GetCommentForm.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) GetCommentForm.h -o moc_GetCommentForm.cpp

moc_MyWindow.cpp: ui_MyWindow.h \
		GetCommentForm.h \
		ui_GetCommentForm.h \
		RetrieveForm.h \
		ui_RetrieveForm.h \
		MyWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MyWindow.h -o moc_MyWindow.cpp

moc_RetrieveForm.cpp: ui_RetrieveForm.h \
		RetrieveForm.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) RetrieveForm.h -o moc_RetrieveForm.cpp

moc_TableModel.cpp: FileRecord.h \
		DBConnector.h \
		VersionRecord.h \
		TableModel.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) TableModel.h -o moc_TableModel.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_GetCommentForm.h ui_MyWindow.h ui_RetrieveForm.h
compiler_uic_clean:
	-$(DEL_FILE) ui_GetCommentForm.h ui_MyWindow.h ui_RetrieveForm.h
ui_GetCommentForm.h: GetCommentForm.ui
	/usr/bin/uic-qt4 GetCommentForm.ui -o ui_GetCommentForm.h

ui_MyWindow.h: MyWindow.ui
	/usr/bin/uic-qt4 MyWindow.ui -o ui_MyWindow.h

ui_RetrieveForm.h: RetrieveForm.ui
	/usr/bin/uic-qt4 RetrieveForm.ui -o ui_RetrieveForm.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

build/Debug/GNU-Linux-x86/CompressUtils.o: CompressUtils.cpp CompressUtils.h \
		ProjectConstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/CompressUtils.o CompressUtils.cpp

build/Debug/GNU-Linux-x86/DBConnector.o: DBConnector.cpp DBConnector.h \
		ProjectConstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/DBConnector.o DBConnector.cpp

build/Debug/GNU-Linux-x86/FileArchiver.o: FileArchiver.cpp FileArchiver.h \
		FileRecord.h \
		DBConnector.h \
		VersionRecord.h \
		ProjectConstants.h \
		MurmurHash3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/FileArchiver.o FileArchiver.cpp

build/Debug/GNU-Linux-x86/FileLib.o: FileLib.cpp FileLib.h \
		MurmurHash3.h \
		ProjectConstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/FileLib.o FileLib.cpp

build/Debug/GNU-Linux-x86/FileRecord.o: FileRecord.cpp FileRecord.h \
		DBConnector.h \
		VersionRecord.h \
		MurmurHash3.h \
		ProjectConstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/FileRecord.o FileRecord.cpp

build/Debug/GNU-Linux-x86/GetCommentForm.o: GetCommentForm.cpp GetCommentForm.h \
		ui_GetCommentForm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/GetCommentForm.o GetCommentForm.cpp

build/Debug/GNU-Linux-x86/MurmurHash3.o: MurmurHash3.cpp MurmurHash3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/MurmurHash3.o MurmurHash3.cpp

build/Debug/GNU-Linux-x86/MyWindow.o: MyWindow.cpp MyWindow.h \
		ui_MyWindow.h \
		GetCommentForm.h \
		ui_GetCommentForm.h \
		RetrieveForm.h \
		ui_RetrieveForm.h \
		FileArchiver.h \
		FileRecord.h \
		DBConnector.h \
		VersionRecord.h \
		TableModel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/MyWindow.o MyWindow.cpp

build/Debug/GNU-Linux-x86/RetrieveForm.o: RetrieveForm.cpp RetrieveForm.h \
		ui_RetrieveForm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/RetrieveForm.o RetrieveForm.cpp

build/Debug/GNU-Linux-x86/TableModel.o: TableModel.cpp TableModel.h \
		FileRecord.h \
		DBConnector.h \
		VersionRecord.h \
		FileArchiver.h \
		FileLib.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/TableModel.o TableModel.cpp

build/Debug/GNU-Linux-x86/TestUtilities.o: TestUtilities.cpp DBConnector.h \
		TestUtilities.h \
		ProjectConstants.h \
		FileRecord.h \
		VersionRecord.h \
		MurmurHash3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/TestUtilities.o TestUtilities.cpp

build/Debug/GNU-Linux-x86/Utilities.o: Utilities.cpp ProjectConstants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Utilities.o Utilities.cpp

build/Debug/GNU-Linux-x86/VersionRecord.o: VersionRecord.cpp VersionRecord.h \
		ProjectConstants.h \
		DBConnector.h \
		MurmurHash3.h \
		CompressUtils.h \
		FileLib.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/VersionRecord.o VersionRecord.cpp

build/Debug/GNU-Linux-x86/main.o: main.cpp ProjectConstants.h \
		FileRecord.h \
		DBConnector.h \
		VersionRecord.h \
		TestUtilities.h \
		FileArchiver.h \
		MyWindow.h \
		ui_MyWindow.h \
		GetCommentForm.h \
		ui_GetCommentForm.h \
		RetrieveForm.h \
		ui_RetrieveForm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/main.o main.cpp

build/Debug/GNU-Linux-x86/moc_GetCommentForm.o: moc_GetCommentForm.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_GetCommentForm.o moc_GetCommentForm.cpp

build/Debug/GNU-Linux-x86/moc_MyWindow.o: moc_MyWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_MyWindow.o moc_MyWindow.cpp

build/Debug/GNU-Linux-x86/moc_RetrieveForm.o: moc_RetrieveForm.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_RetrieveForm.o moc_RetrieveForm.cpp

build/Debug/GNU-Linux-x86/moc_TableModel.o: moc_TableModel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_TableModel.o moc_TableModel.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

