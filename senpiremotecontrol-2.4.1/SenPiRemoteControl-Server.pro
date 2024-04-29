# -------------------------------------------------
# Project created by QtCreator 2009-07-27T19:26:51
# -------------------------------------------------
TARGET = qremotecontrol-server
VERSION = 2.4.1
DEFINES += VERSION=\"\\\"$$VERSION\\\"\"

TRANSLATIONS = i18/de.ts i18/ru.ts i18/uk.ts

include(./qtsingleapplication/qtsingleapplication.pri)

QT += core \
      gui \
      network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent
TEMPLATE = app
SOURCES += main.cpp \
    qremotecontrolserver.cpp \
    qglobalfakekey/qglobalfakekey.cpp \
    usercommanddialog.cpp \
    helpdialog.cpp \
    icondialog.cpp

HEADERS += qremotecontrolserver.h \
    qglobalfakekey/qglobalfakekey_p.h \
    usercommanddialog.h \
    helpdialog.h \
    icondialog.h

FORMS += qremotecontrolserver.ui \
    usercommanddialog.ui \
    helpdialog.ui \
    icondialog.ui

linux-g++ | linux-g++-64 | linux-g++-32 {
#    QT += dbus
    LIBS += -lX11 \
            -lXtst
    SOURCES += qglobalfakekey/qglobalfakekey_x11.cpp
# playwolf/playercontroller.cpp
#    HEADERS += qglobalfakekey_x11.h
# playwolf/playercontroller.h
}
windows {
    LIBS += -lUser32
    SOURCES += qglobalfakekey/qglobalfakekey_win.cpp
#    HEADERS += qglobalfakekey_win.h
    RC_FILE = icon.rc
}
mac {
    LIBS += -framework ApplicationServices -framework Carbon
    SOURCES += qglobalfakekey/qglobalfakekey_osx.cpp \
               qglobalfakekey/mac/qcore_mac.cpp
    HEADERS += qglobalfakekey/mac/qcore_mac_p.h
    ICON = icons/qremotecontrol.icns
}

RESOURCES += icons/icons.qrc \
    images/images.qrc \
    i18/i18.qrc

target.path = /usr/bin

desktop.path = /usr/share/applications
desktop.files = misc/qremotecontrol.desktop

icon.path = /usr/share/pixmaps
icon.files = icons/qremotecontrol.png

INSTALLS += target desktop icon
