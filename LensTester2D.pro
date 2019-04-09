#-------------------------------------------------
#
# Project created by QtCreator 2018-08-16T10:13:34
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = LensTester2D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    circle.cpp \
    mygraphicsview.cpp \
    source.cpp \
    ray.cpp \
    sourcecontextmenu.cpp \
    mygraphicsscene.cpp \
    qgraphicsarcitem.cpp \
    rayorigin.cpp \
    dialogeditcircle.cpp

HEADERS += \
        mainwindow.h \
    circle.h \
    mygraphicsview.h \
    source.h \
    ray.h \
    sourcecontextmenu.h \
    mygraphicsscene.h \
    qgraphicsarcitem.h \
    rayorigin.h \
    ../build-LensTester2D-Desktop_Qt_5_10_1_GCC_64bit2-Debug/ui_dialogeditcircle.h \
    dialogeditcircle.h

FORMS += \
        mainwindow.ui \
    dialogeditcircle.ui \
    dialogeditcircle.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
