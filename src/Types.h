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

#define PROGRAMM_NAME "VpnClient"

using namespace std;
using uint = unsigned int;
enum class AccStatus {Null, Offline, Connecting, Connected};
enum class NicStatus {Enabled, Disabled};

struct Nic {
    QString _deviceName;
    bool    _enable;
    QString _mac_address;
    QString _version;
};

struct AccountData {
    QString _vpnConName;
    bool    _active;
    bool    _connected;
    QString _vpnServerName;
    QString _virtualHub;
    QString _nicName;
};

#endif // TYPES_H
