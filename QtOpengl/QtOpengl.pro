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

CONFIG += c++11 static

SOURCES += \
        camera.cpp \
        colorbutton.cpp \
        glwidget.cpp \
        grid.cpp \
        groupbox.cpp \
        main.cpp \
        mainwindow.cpp \
        mesh.cpp \
        model.cpp \
        objloader.cpp \
        shader.cpp \
        treeview.cpp

HEADERS += \
        camera.h \
        colorbutton.h \
        glwidget.h \
        grid.h \
        groupbox.h \
        mainwindow.h \
        material.h \
        mesh.h \
        model.h \
        objloader.h \
        shader.h \
        treeview.h \
        vertex.h

FORMS += \
        mainwindow.ui

RC_ICONS = QtOpengl.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    models.qrc \
    shaders.qrc \
    textures.qrc
