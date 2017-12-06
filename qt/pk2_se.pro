#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T10:13:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pk2_se
TEMPLATE = app


SOURCES += sc_window.cpp\
        ../src/main.cpp\
        ../src/sprite.cpp\
        ../src/qt_pistesound.cpp\
        ../src/qt_pistedraw.cpp \
        PBox/pboxbool.cpp \
    PBox/pboxnumber.cpp


HEADERS  += sc_window.h\
        ../src/sprite.h\
        ../src/types.h\
        ../src/platform.h \
        ../src/pistedraw.h \
        ../src/pistesound.h\
        ../src/constants.h \
        PBox/pboxbool.h \
    PBox/pboxnumber.h

FORMS    += sc_window.ui
