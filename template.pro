QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/geometry.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp

HEADERS += \
    src/geometry.h \
    src/mainwidget.h \
    src/geometryengine.h

RESOURCES += \
    ressources/shaders.qrc \

DISTFILES +=
