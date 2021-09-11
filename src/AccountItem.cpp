#include "AccountItem.h"

AccountItem::AccountItem(const AccountData &data)
    : _data(data) {

}

QString AccountItem::getTitle() const {
    return _data._vpnConName;
}

Status AccountItem::getStatus() const {
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

QString AccountItem::getStatusStr() const {
    switch (getStatus()) {
    case Status::Null: return "";
    case Status::Offline: return "Offline";
    case Status::Connected: return "Connected";
    case Status::Connecting: return "Connecting";
    }
}

QString AccountItem::getServerHostName() const {
    return _data._vpnServerName;
}

QString AccountItem::getVirtualHub() const {
    return _data._virtualHub;
}

QString AccountItem::getNicName() const {
    return _data._nicName;
}

void AccountItem::doubleClick() {

}
