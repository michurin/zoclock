VERSION = 1.1.2
QT += core gui
CONFIG += release warn_on qt # debug
OBJECTS_DIR = build
MOC_DIR = build
TEMPLATE = app
DEFINES += ZOCVERSION=$$VERSION
DEPENDPATH += .
INCLUDEPATH += .
HEADERS += src/popupmenu.h \
           src/settings.h \
           src/zoclock.h \
           src/zocwidget.h
SOURCES += src/popupmenu.cpp \
           src/settings.cpp \
           src/zoclock.cpp \
           src/zocwidget.cpp
DISTFILES += \
           COPYING \
           README \
           zoclock.pro \
           MANIFEST
TARGET = zoclock

unix {
  install_zoc.path = /usr/local/bin
  install_zoc.commands = $(INSTALL_PROGRAM) $(TARGET) $(INSTALL_ROOT)$$install_zoc.path/$(QMAKE_TARGET)
  INSTALLS += install_zoc
  message("Now type")
  message("  $ make")
  message("  $ sudo make install")
  message("To build and install ZOClock into $$install_zoc.path")
  message("Or specify your favorit path to install like this")
  message("  $ sudo make INSTALL_ROOT=/opt/bin install")
} else {
  message("No install target for your platform")
  message("Install zoclock manualy")
}
