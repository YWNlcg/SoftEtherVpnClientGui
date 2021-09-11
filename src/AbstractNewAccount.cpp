#include "AbstractNewAccount.h"

Status AbstractNewAccount::getStatus() const {
    return Status::Null;
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
