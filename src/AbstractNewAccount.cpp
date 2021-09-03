#include "AbstractNewAccount.h"

Status AbstractNewAccount::getStatus() {
    return Status::Null;
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
