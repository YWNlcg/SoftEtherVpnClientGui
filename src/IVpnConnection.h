#ifndef IVPNCONNECTION_H
#define IVPNCONNECTION_H

#include <QMainWindow>
#include "Types.h"

class IVpnConnection {
public:
    enum Status {Null, Connected, Disconnected};

public:
    virtual QString getName() = 0;
    virtual Status getStatus() = 0;
    virtual QString getVpnServerName() = 0;
    virtual QString getVirtualHub() = 0;
    virtual QString getVirtualNetworkAdapter() = 0;
    virtual void openWindow() = 0;
    virtual ~IVpnConnection() {};
};

#endif // IVPNCONNECTION_H
