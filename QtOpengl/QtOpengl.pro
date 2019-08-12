#-------------------------------------------------
#
# Project created by QtCreator 2019-08-09T13:16:18
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpengl

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        geometryengine.cpp \
        glwidget.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        geometryengine.h \
        glwidget.h \
        mainwindow.h \
        vertex.h

FORMS += \
        mainwindow.ui

RC_ICONS = QtOpengl.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders.qrc
