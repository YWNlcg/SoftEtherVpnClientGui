#include "VpnConnection.h"
#include "ui_VpnConnectionWindow.h"

VpnConnection::VpnConnection(const VpnConnectionItem &item, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::VpnConnection),
      _data(new VpnConnectionItem(item)){
    ui->setupUi(this);
}


VpnConnection::~VpnConnection() {
    delete ui;
    delete _data;
}

QString VpnConnection::getName() {
    return _data->_vpnConName;
}

IVpnConnection::Status VpnConnection::getStatus() {
    Status status;
    if (_data->_connected) {
        status = Status::Connected;
    }
    else if (_data->_active) {
        status = Status::Connecting;
    }
    else {
        status = Status::Disconnected;
    }
    return status;
}

QString VpnConnection::getVpnServerName() {
    return _data->_vpnServerName;
}

QString VpnConnection::getVirtualHub() {
    return _data->_virtualHub;
}

QString VpnConnection::getVirtualNetworkAdapter() {
    return _data->_nicName;
}

void VpnConnection::openWindow() {

}
