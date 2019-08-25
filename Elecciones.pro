#-------------------------------------------------
#
# Project created by QtCreator 2019-08-20T10:24:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Elecciones
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
        adminwin.cpp \
        candidatowin.cpp \
        main.cpp \
        mainwindow.cpp \
        perfilwin.cpp \
        registrowin.cpp \
        resultadoswin.cpp \
        votacionwin.cpp \
        votantewin.cpp \
    usuario.cpp \
    popupcreareleccion.cpp \
    popupfase.cpp

HEADERS += \
        adminwin.h \
        candidatowin.h \
        mainwindow.h \
        perfilwin.h \
        registrowin.h \
        resultadoswin.h \
        votacionwin.h \
        votantewin.h \
    usuario.h \
    popupcreareleccion.h \
    popupfase.h

FORMS += \
        adminwin.ui \
        candidatowin.ui \
        mainwindow.ui \
        perfilwin.ui \
        registrowin.ui \
        resultadoswin.ui \
        votacionwin.ui \
        votantewin.ui \
    popupcreareleccion.ui \
    popupfase.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
