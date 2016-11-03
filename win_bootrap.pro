QT       -= core gui widgets

CONFIG += c++11

TARGET = bootstrap_win_pyTSon
TEMPLATE = lib

DESTDIR = $$PWD/build
OBJECTS_DIR = $$PWD/build
MOC_DIR = $$PWD/build
RCC_DIR = $$PWD/build
UI_DIR = $$PWD/build

INCLUDEPATH += ../../includes/pluginsdk/21/include

SOURCES += bootstrap.cpp

HEADERS += bootstrap.h

