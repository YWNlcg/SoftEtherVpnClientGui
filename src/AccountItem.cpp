#include "AccountItem.h"

AccountItem::AccountItem(const AccountData &data)
    : _data(data) {

}

QString AccountItem::getTitle() const {
    return _data._vpnConName;
}

AccStatus AccountItem::getStatus() const {
    AccStatus status;
    if (_data._connected) {
        status = AccStatus::Connected;
    }
    else if (_data._active) {
        status = AccStatus::Connecting;
    }
    else {
        status = AccStatus::Offline;
    }
    return status;
}

QString AccountItem::getStatusStr() const {
    switch (getStatus()) {
    case AccStatus::Null: return "";
    case AccStatus::Offline: return "Offline";
    case AccStatus::Connected: return "Connected";
    case AccStatus::Connecting: return "Connecting";
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
