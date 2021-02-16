#-------------------------------------------------
#
# Project created by QtCreator 2020-12-27T01:05:33
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += network

TARGET = ElectromagneticDog
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    login.cpp \
    mainwidget.cpp \
    chatwidget.cpp \
    friendbutton.cpp \
    chatsocket.cpp \
    serverinfo.cpp \
    frilist.cpp \
    music.cpp

HEADERS += \
        login.h \
    mainwidget.h \
    chatwidget.h \
    friendbutton.h \
    fixedvalue.h \
    chatsocket.h \
    apply_protocl.h \
    serverinfo.h \
    frilist.h \
    music.h

FORMS += \
        login.ui \
    mainwidget.ui \
    chatwidget.ui \
    serverinfo.ui

CONFIG += mobility
MOBILITY =

RESOURCES += \
    img.qrc

