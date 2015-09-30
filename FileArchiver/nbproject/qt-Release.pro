# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = FileArchiver
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += CompressUtils.cpp DBConfigurationFileUtility.cpp DBConnector.cpp FileArchiver.cpp FileLib.cpp FileRecord.cpp GetCommentForm.cpp MurmurHash3.cpp MyWindow.cpp RetrieveForm.cpp TableModel.cpp TestUtilities.cpp Utilities.cpp VersionRecord.cpp main.cpp
HEADERS += CompressUtils.h DBConnector.h FileArchiver.h FileLib.h FileRecord.h GetCommentForm.h MurmurHash3.h MyWindow.h ProjectConstants.h RetrieveForm.h TableModel.h TestUtilities.h VersionRecord.h
FORMS += GetCommentForm.ui MyWindow.ui RetrieveForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
