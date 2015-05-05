#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T01:16:44
#
#-------------------------------------------------

QT += core gui opengl

QMAKE_CXXFLAGS_RELEASE -= O2
QMAKE_CXXFLAGS_RELEASE += O3

TARGET = MyLE
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    inputmanager.cpp \
    sprite.cpp \
    resourcemanager.cpp \
    texturecache.cpp \
    glwidget.cpp

HEADERS += \
    inputmanager.h \
    sprite.h \
    vertex.h \
    resourcemanager.h \
    texturecache.h \
    glwidget.h

RESOURCES +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}
