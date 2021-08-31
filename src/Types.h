#ifndef TYPES_H
#define TYPES_H

#define OS_UNIX


#define MEMCHECK false
#define SERVICE_DEBUG false

#include <QObject>
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>
#include <QDateTime>
#include <QTextStream>
#include <QErrorMessage>
#include <QMap>
#include <QDebug>
#include <QString>

#include <iostream>
#include <cstring>

using namespace std;

void log_handler(QtMsgType type, const char *msg);

#define PROGRAMM_NAME "VpnClient"
using uint = unsigned int;

struct Nic {
    QString _deviceName;
    bool    _enable;
    QString _mac_address;
    QString _version;
};

struct VpnConnectionItem {
    QString _vpnConName;
    bool    _connected;
    QString _vpnServerName;
    QString _virtualHub;
    QString _nicName;
};

#endif // TYPES_H
