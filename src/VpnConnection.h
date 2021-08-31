#ifndef VPNCONNECTION_H
#define VPNCONNECTION_H

#include <QMainWindow>

#include "CTypes.h"
#include "Types.h"
#include "IVpnConnection.h"
#include "CmdAdapter.h"

namespace Ui {
class VpnConnection;
}

class VpnConnection : public QMainWindow, public IVpnConnection {
    Q_OBJECT

public:
    explicit VpnConnection(const VpnConnectionItem& item,
                           QWidget *parent = nullptr);
    ~VpnConnection();

private:
    Ui::VpnConnection *ui;

    // IVpnConnection interface
public:
    QString getName() override;
    Status getStatus() override;
    QString getVpnServerName() override;
    QString getVirtualHub() override;
    QString getVirtualNetworkAdapter() override;
    void openWindow() override;

private:
    VpnConnectionItem* _data;
};

#endif // VPNCONNECTION_H
