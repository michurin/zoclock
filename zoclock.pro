VERSION = 1.0.0
QT += core gui
CONFIG += release warn_on qt
# CONFIG += qt debug
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
TEMPLATE = app
DEFINES += ZOCVERSION=$$VERSION
DEPENDPATH += .
INCLUDEPATH += .
HEADERS += src/popupmenu.h \
           src/settings.h \
           src/zocdot.h \
           src/zoclock.h \
           src/zocwidget.h
SOURCES += src/popupmenu.cpp \
           src/settings.cpp \
           src/zocdot.cpp \
           src/zoclock.cpp \
           src/zocwidget.cpp
TARGET = zoclock
