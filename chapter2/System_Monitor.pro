#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T19:59:33
#
#-------------------------------------------------

QT       += core gui charts
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = System_Monitor
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
        mainwindow.cpp \
        system_info.cpp \
    system_info_widget.cpp \
    cpu_widget.cpp \
    memory_widget.cpp

HEADERS += \
        mainwindow.h \
        system_info.h \
    system_info_widget.h \
    cpu_widget.h \
    memory_widget.h

windows {
    SOURCES += windows_system_info.cpp
    HEADERS += windows_system_info.h
}

linux {
    SOURCES += linux_system_info.cpp
    HEADERS += linux_system_info.h
}

FORMS += mainwindow.ui
