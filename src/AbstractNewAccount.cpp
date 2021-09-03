#include "AbstractNewAccount.h"

Status AbstractNewAccount::getStatus() {
    return Status::Null;
}

QString AbstractNewAccount::getStatusStr() {
    return QString();
}

QString AbstractNewAccount::getServerHostName() {
    return QString();
}

QString AbstractNewAccount::getVirtualHub() {
    return QString();
}

QString AbstractNewAccount::getNicName() {
    return QString();
}
