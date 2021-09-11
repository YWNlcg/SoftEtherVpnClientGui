#include "AbstractNewAccount.h"

AccStatus AbstractNewAccount::getStatus() const {
    return AccStatus::Null;
}

QString AbstractNewAccount::getStatusStr() const {
    return QString();
}

QString AbstractNewAccount::getServerHostName() const {
    return QString();
}

QString AbstractNewAccount::getVirtualHub() const {
    return QString();
}

QString AbstractNewAccount::getNicName() const {
    return QString();
}
