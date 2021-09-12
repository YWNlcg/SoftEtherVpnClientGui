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

#include "CTypes.h"

#define PROGRAMM_NAME "VpnClient"
#define AUTH_TYPE_ANONYMOUS CLIENT_AUTHTYPE_ANONYMOUS
#define AUTH_TYPE_PASSWORD  CLIENT_AUTHTYPE_PASSWORD
#define AUTH_TYPE_RADIUS    CLIENT_AUTHTYPE_PLAIN_PASSWORD
#define AUTH_TYPE_CERT      CLIENT_AUTHTYPE_CERT
#define AUTH_TYPE_SMARTCARD CLIENT_AUTHTYPE_SECURE

using namespace std;
using uint = unsigned int;
enum class AccStatus {Null, Offline, Connecting, Connected};
enum class NicStatus {Enabled, Disabled};
enum class AuthType {
    Anonymous = AUTH_TYPE_ANONYMOUS,
    Password = AUTH_TYPE_PASSWORD,
    Radius = AUTH_TYPE_RADIUS,
    Certificate = AUTH_TYPE_CERT,
    SmartCard = AUTH_TYPE_SMARTCARD,
    Unknown
};

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
