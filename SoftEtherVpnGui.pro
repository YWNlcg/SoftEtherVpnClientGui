QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/AccountAdapter.cpp \
    src/CmdAdapter.cpp \
    src/MainWindow.cpp \
    src/NewVpnConnection.cpp \
    src/VpnClient.cpp \
    src/VpnConnection.cpp \
    src/main.cpp \
    src/loghandler.cpp

HEADERS += \
    src/AccountAdapter.h \
    src/CTypes.h \
    src/CmdAdapter.h \
    src/IVpnConnection.h \
    src/MainWindow.h \
    src/NewVpnConnection.h \
    src/Types.h \
    src/VpnClient.h \
    src/VpnConnection.h

FORMS += \
    ui/MainWindow.ui \
    ui/NewVpnConnectionWindow.ui \
    ui/VpnConnectionWindow.ui

INCLUDEPATH += \
    SoftEtherVPN/src/

LIBS += \
    -lcedar \
    -lmayaqua


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target