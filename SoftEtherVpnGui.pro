QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
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
=======
    src/AbstractNewAccount.cpp \
    src/AccountItem.cpp \
    src/ContextMenuAccount.cpp \
    src/ContextMenuNic.cpp \
    src/MainWindow.cpp \
    src/NewAccountItem.cpp \
    src/NewVpnConnectionDialog.cpp \
    src/NicItem.cpp \
    src/main.cpp    \
    src/CmdAdapter.cpp \
    src/VpnClient.cpp

HEADERS += \
    src/AbstractNewAccount.h \
    src/AccountItem.h \
    src/ContextMenuAccount.h \
    src/ContextMenuNic.h \
    src/Extern.h \
    src/IAccountItem.h \
    src/INicItem.h \
    src/MainWindow.h \
    src/CmdAdapter.h \
    src/CTypes.h \
    src/NewAccountItem.h \
    src/NewVpnConnectionDialog.h \
    src/NicItem.h \
    src/Types.h \
    src/VpnClient.h

FORMS += \
    ui/MainWindow.ui \
    ui/NewVpnConnectionDialog.ui \
    ui/NewVpnConnectionWindow.ui
>>>>>>> restart-project

INCLUDEPATH += \
    SoftEtherVPN/src/

LIBS += \
    -lcedar \
    -lmayaqua


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
