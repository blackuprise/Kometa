#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T20:23:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kometa
TEMPLATE = app


HEADERS += src/SongItem.h \
    src/SongViewDelegate.h \
    src/Song.h \
    src/Constants.h \
    src/MediaPlayer.h \
    src/kometa.h
SOURCES += src/SongItem.cpp \
    src/SongViewDelegate.cpp \
    src/Song.cpp \
    src/MediaPlayer.cpp \
    src/SoundEventReceiver.cpp \
    src/kometa.cpp \
    src/main.cpp
FORMS    += ui/kometa.ui

RESOURCES += \
    resources/kometa_resource.qrc



unix:!macx: LIBS += -L$$PWD/libs/irrKlang-64bit-1.5.0/bin/linux-gcc-64/ -lIrrKlang

INCLUDEPATH += $$PWD/libs/irrKlang-64bit-1.5.0/include
DEPENDPATH += $$PWD/libs/irrKlang-64bit-1.5.0/include



unix:!macx: LIBS += -L$$PWD/libs/id3lib-3.8.3/src/.libs/ -lid3

INCLUDEPATH += $$PWD/libs/id3lib-3.8.3/include
DEPENDPATH += $$PWD/libs/id3lib-3.8.3/include
