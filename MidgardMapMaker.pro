#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T22:57:17
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MidgardMapMaker
TEMPLATE = app


SOURCES += main.cpp\
        mapmaker.cpp \
    terrainpainter.cpp \
    updater.cpp \
    mapname.cpp \
    mapsize.cpp

HEADERS  += mapmaker.h \
    terrainpainter.h \
    updater.h \
    mapname.h \
    mapsize.h

FORMS    += mapmaker.ui \
    mapname.ui \
    mapsize.ui

RESOURCES += \
    resource.qrc
