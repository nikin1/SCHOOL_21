QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += widgets opengl openglwidgets
#LIBS +=-lopengl32 -lglu32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#DEFINES += GL_SILENCE_DEPRECATION

SOURCES += \
    geometry.cpp \
    main.cpp \
    mainwindow.cpp \
    s21_3Dviewer.c \
    widget.cpp

HEADERS += \
    geometry.h \
    mainwindow.h \
    s21_3Dviewer.h \
    widget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cube_norm.obj \
    vshader.glsl \
    vshader.glsl

RESOURCES += \
    fshader.qrc \
    fshader.qrc \
    vshader.qrc
