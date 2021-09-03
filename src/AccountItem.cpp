#include "AccountItem.h"

AccountItem::AccountItem(QWidget *parent, const AccountData &data)
    : _data(data) {

}

QString AccountItem::getTitle() {
    return _data._vpnConName;
}

Status AccountItem::getStatus() {
    Status status;
    if (_data._connected) {
        status = Status::Connected;
    }
    else if (_data._active) {
        status = Status::Connecting;
    }
    else {
        status = Status::Offline;
    }
    return status;
}

QString AccountItem::getServerHostName() {
    return _data._vpnServerName;
}

QString AccountItem::getVirtualHub() {
    return _data._virtualHub;
}

QString AccountItem::getNicName() {
    return _data._nicName;
}

void AccountItem::doubleClick() {

}
