#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T01:16:44
#
#-------------------------------------------------

QT += core gui opengl

TARGET = MyLE
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    inputmanager.cpp \
    sprite.cpp \
    resourcemanager.cpp \
    texturecache.cpp

HEADERS += \
    inputmanager.h \
    sprite.h \
    vertex.h \
    resourcemanager.h \
    texturecache.h

DISTFILES +=

RESOURCES +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}
