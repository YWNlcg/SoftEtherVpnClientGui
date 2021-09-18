#include "AccountAdapter.h"

AccountAdapter::AccountAdapter() {
    logDebug(DefLog, "Create AccountAdapter");
    alloc();
    init();
}

AccountAdapter::AccountAdapter(const RpcGtAc *other) {
    logDebug(DefLog, "Create AccountAdapter");
    alloc();
    copy(_account, other);
}

AccountAdapter::~AccountAdapter() {
    logDebug(DefLog, "Destruct AccountAdapter");
    free();
}

int AccountAdapter::setAccountName(const QString &accountName) {
    logDebug(DefLog, "Set account name: %s", accountName.toStdString().c_str());
    if (accountName.size() > MAX_ACCOUNT_NAME_LEN) {
        logCritical(DefLog, "Account name is too long: %s", accountName.toStdString().c_str());
        return ERROR_ACCOUNT_NAME_IS_LONG;
    }
    wcscpy(_account->ClientOption->AccountName, accountName.toStdWString().c_str());
    return NO_ERROR;
}

QString AccountAdapter::getAccountName() const {
    return QString::fromWCharArray(_account->ClientOption->AccountName);
}

int AccountAdapter::setHostName(const QString& hostName) {
    logDebug(DefLog, "Set host name: %s", hostName.toStdString().c_str());
    if (hostName.size() > MAX_HOST_NAME_LEN) {
        logCritical(DefLog, "Host name is too long: %s", hostName.toStdString().c_str());
        return ERROR_HOST_NAME_IS_LONG;
    }
    strncpy(_account->ClientOption->Hostname, hostName.toStdString().c_str(), hostName.size());
    return NO_ERROR;
}

QString AccountAdapter::getHostName() const {
    return QString(_account->ClientOption->Hostname);
}

void AccountAdapter::setPort(unsigned short port, PortType pType) {
    logDebug(DefLog, "Set port: %d", port);
    if (pType == PortType::TCP) {
        _account->ClientOption->Port = port;
        _account->ClientOption->PortUDP = 0;
    }
    else if (pType == PortType::UDP) {
        _account->ClientOption->Port = 0;
        _account->ClientOption->PortUDP = port;
    }
    else {
        logCritical(DefLog, "Unknown port type: %d", int(pType));
    }
}

unsigned int AccountAdapter::getPort() const {
    logDebug(DefLog, "Get port");
    auto port = _account->ClientOption->Port;
    auto portUdp = _account->ClientOption->PortUDP;
    return portUdp != 0 ? portUdp : port;
}

AccountAdapter::PortType AccountAdapter::getPortType() const {
    logDebug(DefLog, "Get Port Type");
    return _account->ClientOption->PortUDP == 0 ? PortType::TCP : PortType::UDP;
}

int AccountAdapter::setHubName(const QString &hubName) {
    logDebug(DefLog, "Set hub name: %s", hubName.toStdString().c_str());
    if (hubName.size() > MAX_HUBNAME_LEN) {
        logCritical(DefLog, "Hub name is too long: %s", hubName.toStdString().c_str());
        return ERROR_HUB_NAME_IS_LONG;
    }
    strncpy(_account->ClientOption->HubName, hubName.toStdString().c_str(), hubName.size());
    return NO_ERROR;
}

QString AccountAdapter::getHubName() const {
    logDebug(DefLog, "Get hub name");
    return QString(_account->ClientOption->HubName);
}

int AccountAdapter::setDeviceName(const QString &deviceName) {
    logDebug(DefLog, "Set device dame: %s", deviceName.toStdString().c_str());
    if (deviceName.size() > MAX_DEVICE_NAME_LEN) {
        logCritical(DefLog, "Device name is too long: %s", deviceName.toStdString().c_str());
        return ERROR_DEVICE_NAME_IS_LONG;
    }
    strncpy(_account->ClientOption->DeviceName, deviceName.toStdString().c_str(), deviceName.size());
    return NO_ERROR;
}

QString AccountAdapter::getDeviceName() const {
    logDebug(DefLog, "Get device name");
    return QString(_account->ClientOption->DeviceName);
}

void AccountAdapter::setAuthType(AuthType type) {
    logDebug(DefLog, "Set type auth: %d", int(type));
    _account->ClientAuth->AuthType = (unsigned int)type;
}

AuthType AccountAdapter::getAuthType() const {
    return AuthType(_account->ClientAuth->AuthType);
}

int AccountAdapter::setUserName(const QString &userName) {
    logDebug(DefLog, "Set user dame: %s", userName.toStdString().c_str());
    if (userName.size() > MAX_USERNAME_LEN) {
        logCritical(DefLog, "User name is too long: %s", userName.toStdString().c_str());
        return ERROR_USER_NAME_IS_LONG;
    }
    strncpy(_account->ClientAuth->Username, userName.toStdString().c_str(), userName.size());
    return NO_ERROR;
}

QString AccountAdapter::getUserName() const {
    logDebug(DefLog, "Get user name");
    return QString(_account->ClientAuth->Username);
}

int AccountAdapter::setPassword(const QString &pass) {
    logDebug(DefLog, "Set password: %s", pass.toStdString().c_str());
    if (pass.size() > MAX_PASSWORD_LEN) {
        logCritical(DefLog, "Password is too long: %s", pass.toStdString().c_str());
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
    logDebug(DefLog, "Get password");
    return QString(_account->ClientAuth->PlainPassword);
}

RpcCrAc *AccountAdapter::getRpcClientCreateAccount() {
    logDebug(DefLog, "Get RPC_CLIENT_CREATE_ACCOUNT");
    return (RpcCrAc*)_account;
}

void AccountAdapter::alloc() {
    _account = new RpcCrAc;
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

void AccountAdapter::copy(RpcCrAc *dest, const RpcGtAc *src) {
    auto copySrc = (RpcCrAc*)(src + MAX_ACCOUNT_NAME_LEN + 1);
    memcpy(dest, copySrc, sizeof(RpcCrAc));
}
