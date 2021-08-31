#include "AccountAdapter.h"

AccountAdapter::AccountAdapter() {
    alloc();
    init();
}

AccountAdapter::AccountAdapter(const RpcGtAc *other) {
    alloc();
    copy(_account, other);
}

AccountAdapter::AccountAdapter(const RpcCrAc *other) {
    alloc();
    auto copyAccount = (RpcCrAc*)_account;
    copy(copyAccount, other);
}

AccountAdapter::~AccountAdapter() {
    free();
}

int AccountAdapter::setAccountName(const QString &accountName) {
    if (accountName.size() > MAX_ACCOUNT_NAME_LEN) {
        return ERROR_ACCOUNT_NAME_IS_LONG;
    }
    wcscpy(_account->ClientOption->AccountName, accountName.toStdWString().c_str());
    return NO_ERROR;
}

QString AccountAdapter::getAccountName() const {
    return QString::fromWCharArray(_account->ClientOption->AccountName);
}

int AccountAdapter::setHostName(const QString& hostName) {
    if (hostName.size() > MAX_HOST_NAME_LEN) {
        return ERROR_HOST_NAME_IS_LONG;
    }
    strncpy(_account->ClientOption->Hostname, hostName.toStdString().c_str(), hostName.size());
    return NO_ERROR;
}

QString AccountAdapter::getHostName() const {
    return QString(_account->ClientOption->Hostname);
}

void AccountAdapter::setPort(unsigned short port, PortType pType) {
    if (pType == PortType::TCP) {
        _account->ClientOption->Port = port;
        _account->ClientOption->PortUDP = 0;
    }
    else if (pType == PortType::UDP) {
        _account->ClientOption->Port = 0;
        _account->ClientOption->PortUDP = port;
    }
    else {
        qDebug() << "Port is xz";
    }
}

unsigned int AccountAdapter::getPort() const {
    auto port = _account->ClientOption->Port;
    auto portUdp = _account->ClientOption->PortUDP;
    return portUdp != 0 ? portUdp : port;
}

AccountAdapter::PortType AccountAdapter::getPortType() const {
    return _account->ClientOption->PortUDP == 0 ? PortType::TCP : PortType::UDP;
}

int AccountAdapter::setHubName(const QString &hubName) {
    if (hubName.size() > MAX_HUBNAME_LEN) {
        return ERROR_HUB_NAME_IS_LONG;
    }
    strncpy(_account->ClientOption->HubName, hubName.toStdString().c_str(), hubName.size());
    return NO_ERROR;
}

QString AccountAdapter::getHubName() const {
    return QString(_account->ClientOption->HubName);
}

int AccountAdapter::setDeviceName(const QString &deviceName) {
    if (deviceName.size() > MAX_DEVICE_NAME_LEN) {
        return ERROR_DEVICE_NAME_IS_LONG;
    }
    strncpy(_account->ClientOption->DeviceName, deviceName.toStdString().c_str(), deviceName.size());
    return NO_ERROR;
}

QString AccountAdapter::getDeviceName() const {
    return QString(_account->ClientOption->DeviceName);
}

void AccountAdapter::setAuthType(AuthType type) {
    _account->ClientAuth->AuthType = (unsigned int)type;
}

AccountAdapter::AuthType AccountAdapter::getAuthType() const {
    return AuthType(_account->ClientAuth->AuthType);
}

int AccountAdapter::setUserName(const QString &userName) {
    if (userName.size() > MAX_USERNAME_LEN) {
        return ERROR_USER_NAME_IS_LONG;
    }
    strncpy(_account->ClientAuth->Username, userName.toStdString().c_str(), userName.size());
    return NO_ERROR;
}

QString AccountAdapter::getUserName() const {
    return QString(_account->ClientAuth->Username);
}

int AccountAdapter::setPassword(const QString &pass) {
    if (pass.size() > MAX_PASSWORD_LEN) {
        return ERROR_PASSWORD_IS_LONG;
    }
    char* copyPass = new char[pass.size() + 1];
    Zero(copyPass, pass.size() + 1);
    strncpy(copyPass, pass.toStdString().c_str(), pass.size());
    strncpy(_account->ClientAuth->PlainPassword, copyPass, pass.size());
    Sha1(_account->ClientAuth->HashedPassword, copyPass, pass.size());
    delete[] copyPass;
    return NO_ERROR;
}

QString AccountAdapter::getPassword() const {
    return QString(_account->ClientAuth->PlainPassword);
}

RpcCrAc *AccountAdapter::getRpcClientCreateAccount() {
    return (RpcCrAc*)_account;
}

void AccountAdapter::alloc() {
    _account = new RpcGtAc;
    Zero(_account, sizeof(_account));

    _account->ClientOption = new CLIENT_OPTION;
    Zero(_account->ClientOption, sizeof(_account->ClientOption));

    _account->ClientAuth = new CLIENT_AUTH;
    Zero(_account->ClientAuth, sizeof(_account->ClientAuth));
//    _account->ClientAuth->ClientX = new X;
//    _account->ClientAuth->ClientK = new K;
//    _account->ServerCert = new X;
}

void AccountAdapter::free() {
    delete _account->ClientOption;
    delete _account->ClientAuth;
//    delete _account->ServerCert;
    delete _account;
}

void AccountAdapter::init() {
    _account->ClientOption->NumRetry = UINT32_MAX;
    _account->ClientOption->RetryInterval = 15;
    _account->ClientOption->MaxConnection = 1;
    _account->ClientOption->UseEncrypt = 1;
    _account->ClientOption->AdditionalConnectionInterval = 1;
}

void AccountAdapter::copy(RpcCrAc *dest, const RpcCrAc *src) {
    memcpy(dest, src, sizeof(RpcCrAc));
    memcpy(dest->ClientOption, src->ClientOption, sizeof(CLIENT_OPTION));
    memcpy(dest->ClientAuth, src->ClientAuth, sizeof(CLIENT_AUTH));
}

void AccountAdapter::copy(RpcGtAc *dest, const RpcGtAc *src) {
    auto copyDest = (RpcCrAc*)dest;
    auto copySrc = (RpcCrAc*)src;
    copy(copyDest, copySrc);
    dest->UpdateDateTime = src->UpdateDateTime;
    dest->CreateDateTime = src->CreateDateTime;
    dest->LastConnectDateTime = src->LastConnectDateTime;
}
