QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/Camera.cpp \
    src/ChewToyModel.cpp \
    src/GeometryEngine.cpp \
    src/MainWidget.cpp \
    src/MainWindow.cpp \
    src/ModelVertex.cpp \
    src/Skybox.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/Camera.h \
    src/ChewToyModel.h \
    src/GeometryEngine.h \
    src/MainWidget.h \
    src/MainWindow.h \
    src/ModelVertex.h \
    src/Skybox.h \
    src/mainwidget.h \
    src/geometryengine.h \
    src/mainwindow.h

RESOURCES += \
    ressources/shaders.qrc \

DISTFILES +=

FORMS += \
    src/mainwindow.ui
