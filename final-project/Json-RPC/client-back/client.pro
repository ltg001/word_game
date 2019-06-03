#-------------------------------------------------
#
# Project created by QtCreator 2019-05-11T14:54:00
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    client.cpp \
    person.cpp \
    client.cpp \
    game.cpp \
    login_window.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    player.cpp \
    register_window.cpp \
    reset_pwd.cpp \
    setter.cpp \
    view_all_question.cpp

HEADERS += \
        mainwindow.h \
    include.h \
    client.h \
    client.h \
    game.h \
    include.h \
    login_window.h \
    mainwindow.h \
    player.h \
    register_window.h \
    reset_pwd.h \
    setter.h \
    view_all_question.h

FORMS += \
        mainwindow.ui \
    client.ui \
    client.ui \
    game.ui \
    login_window.ui \
    mainwindow.ui \
    player.ui \
    register_window.ui \
    reset_pwd.ui \
    setter.ui \
    view_all_question.ui

SUBDIRS += \
    client.pro

DISTFILES += \
    client.pro.user
