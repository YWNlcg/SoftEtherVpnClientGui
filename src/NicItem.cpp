#include "NicItem.h"

NicItem::NicItem(const Nic &nic) {
    _nic._deviceName = nic._deviceName;
    _nic._enable = nic._enable;
    _nic._mac_address = nic._mac_address;
    _nic._version = nic._version;
}

QString NicItem::getTitle() const {
    return _nic._deviceName;
}

NicStatus NicItem::getStatus() const {
    return _nic._enable ? NicStatus::Enabled : NicStatus::Disabled;
}

QString NicItem::getStatusStr() const {
    return _nic._enable ? "Enable" : "Disable";
}

QString NicItem::getMacAddr() const {
    return _nic._mac_address;
}

QString NicItem::getVersion() const {
    return _nic._version;
}
