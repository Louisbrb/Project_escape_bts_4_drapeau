# -------------------------------------------------
# Project created by QtCreator 2014-11-25T16:21:40
# -------------------------------------------------
QT -= gui
TARGET = compteur_balle
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    application.cpp \
    ressources.cpp \
    utils.cpp \
    VisionMode.cpp \
    StatusCheck.cpp \
    Speaker.cpp \
    log_file.cpp \
    application_compteur_balle.cpp
HEADERS += application.h \
    ressources.h \
    utils.h \
    VisionMode.h \
    StatusCheck.h \
    define.h \
    Speaker.h \
    log_file.h \
    application_compteur_balle.h
LIBS += -lpthread \
    -ljpeg \
    -lrt \
    /darwin/Linux/lib/darwin.a \
    -lespeak
INCLUDEPATH += /darwin/Framework/include \
    /darwin/Linux/include \
    /darwin/Linux/lib \
    DEPENDPATH \
    += \
    /darwin/Framework/include \
    /darwin/Linux/include \
    /darwin/Linux/lib \
    /usr/include/espeak
PRE_TARGETDEPS += /usr/lib/libespeak.a
