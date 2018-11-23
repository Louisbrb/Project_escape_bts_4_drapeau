# -------------------------------------------------
# Project created by QtCreator 2014-11-25T16:21:40
# -------------------------------------------------
QT -= gui
TARGET = escape_game
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
    /home/darwin/Desktop/ESCAPE_GAME/Linux/lib/darwin.a \
    -lespeak
INCLUDEPATH += /home/darwin/Desktop/ESCAPE_GAME/Framework/include \
    /home/darwin/Desktop/ESCAPE_GAME/Linux/include \
    /home/darwin/Desktop/ESCAPE_GAME/Linux/lib \
    DEPENDPATH \
    += \
    /home/darwin/Desktop/ESCAPE_GAME/Framework/include \
    /home/darwin/Desktop/ESCAPE_GAME/Linux/include \
    /home/darwin/Desktop/ESCAPE_GAME/Linux/lib \
    /usr/include/espeak
PRE_TARGETDEPS += /usr/lib/libespeak.a
