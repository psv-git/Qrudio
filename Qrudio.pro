# Copyright (c) 2018 PSV LGPL-3.0
# https://github.com/psv-git

#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T01:44:50
#
#-------------------------------------------------

QT += \
    core gui \
    sql \
    multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qrudio

TEMPLATE = app

RC_ICONS = ./res/icons/qrudio.ico


SUBDIRS += \
    Qrudio.pro


INCLUDEPATH += \
    ./src \
    src/data \
    src/global \
    src/forms \
    src/handlers \
    src/windows


SOURCES += \
    src/main.cpp \
    src/data/DataRecord.cpp \
    src/data/TrackMetaData.cpp \
    src/global/GlobalFunctions.cpp \
    src/handlers/ErrorHandler.cpp \
    src/handlers/SettingsHandler.cpp \
    src/handlers/DataBaseHandler.cpp \
    src/handlers/PlayerHandler.cpp \
    src/windows/PlayerWindow.cpp


HEADERS += \
    src/headers.hpp \
    src/data/DataRecord.hpp \
    src/data/TrackMetaData.hpp \
    src/global/GlobalVariables.hpp \
    src/global/GlobalClasses.hpp \
    src/global/GlobalFunctions.hpp \
    src/handlers/ErrorHandler.hpp \
    src/handlers/SettingsHandler.hpp \
    src/handlers/DataBaseHandler.hpp \
    src/handlers/PlayerHandler.hpp \
    src/windows/PlayerWindow.hpp


FORMS += \
    src/forms/PlayerWindow.ui \
    src/forms/ErrorWindow.ui


DISTFILES += \
    LICENSE \
    README.md \
    res/icons/dark-theme/add-1.svg \
    res/icons/dark-theme/add-2.svg \
    res/icons/dark-theme/backward.svg \
    res/icons/dark-theme/delete.svg \
    res/icons/dark-theme/edit-1.svg \
    res/icons/dark-theme/edit-2.svg \
    res/icons/dark-theme/forward.svg \
    res/icons/dark-theme/loading.svg \
    res/icons/dark-theme/play.svg \
    res/icons/dark-theme/qrudio.svg \
    res/icons/dark-theme/record.svg \
    res/icons/dark-theme/save.svg \
    res/icons/dark-theme/search.svg \
    res/icons/dark-theme/settings.svg \
    res/icons/dark-theme/stop.svg \
    res/icons/dark-theme/tray-off.svg \
    res/icons/dark-theme/tray-on.svg \
    res/icons/light-theme/add-1.svg \
    res/icons/light-theme/add-2.svg \
    res/icons/light-theme/backward.svg \
    res/icons/light-theme/delete.svg \
    res/icons/light-theme/edit-1.svg \
    res/icons/light-theme/edit-2.svg \
    res/icons/light-theme/forward.svg \
    res/icons/light-theme/loading.svg \
    res/icons/light-theme/play.svg \
    res/icons/light-theme/qrudio.svg \
    res/icons/light-theme/record.svg \
    res/icons/light-theme/save.svg \
    res/icons/light-theme/search.svg \
    res/icons/light-theme/settings.svg \
    res/icons/light-theme/stop.svg \
    res/icons/light-theme/tray-off.svg \
    res/icons/light-theme/tray-on.svg \
    res/icons/qrudio.ico


RESOURCES += \
    res/Resources.qrc
