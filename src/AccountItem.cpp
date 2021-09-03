#include "AccountItem.h"

AccountItem::AccountItem(const AccountData &data)
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

QString AccountItem::getStatusStr() {
    switch (getStatus()) {
    case Status::Null: return "";
    case Status::Offline: return "Offline";
    case Status::Connected: return "Connected";
    case Status::Connecting: return "Connecting";
    }
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
