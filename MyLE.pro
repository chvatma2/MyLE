QT += core gui widgets

SOURCES += \
    main.cpp \
    glwidget.cpp \
    inputmanager.cpp \
    sprite.cpp \
    resourcemanager.cpp \
    texturecache.cpp

HEADERS += \
    glwidget.h \
    inputmanager.h \
    sprite.h \
    vertex.h \
    resourcemanager.h \
    texturecache.h

DISTFILES += \
    fragshader.frag \
    vertshader.vert

RESOURCES += \
    resources.qrc
