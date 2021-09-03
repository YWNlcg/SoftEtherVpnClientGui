QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/AbstractNewAccount.cpp \
    src/AccountItem.cpp \
    src/ContextMenuAccount.cpp \
    src/ContextMenuNic.cpp \
    src/MainWindow.cpp \
    src/NewAccountItem.cpp \
    src/main.cpp    \
    src/CmdAdapter.cpp \
    src/VpnClient.cpp

HEADERS += \
    src/AbstractNewAccount.h \
    src/AccountItem.h \
    src/ContextMenuAccount.h \
    src/ContextMenuNic.h \
    src/IAccountItem.h \
    src/IContextMenu.h \
    src/MainWindow.h \
    src/CmdAdapter.h \
    src/CTypes.h \
    src/NewAccountItem.h \
    src/Types.h \
    src/VpnClient.h

FORMS += \
    ui/MainWindow.ui \

INCLUDEPATH += \
    SoftEtherVPN/src/

LIBS += \
    -lcedar \
    -lmayaqua


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
