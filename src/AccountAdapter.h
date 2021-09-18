#ifndef ACCOUNTADAPTER_H
#define ACCOUNTADAPTER_H

#include "Types.h"
#include "CTypes.h"
#include "LogHandler.h"

using RpcCrAc = RPC_CLIENT_CREATE_ACCOUNT;
using RpcGtAc = RPC_CLIENT_GET_ACCOUNT;

#define NO_ERROR 0
#define ERROR_ACCOUNT_NAME_IS_LONG 10
#define ERROR_HOST_NAME_IS_LONG 11
#define ERROR_HUB_NAME_IS_LONG 12
#define ERROR_DEVICE_NAME_IS_LONG 13
#define ERROR_PASSWORD_IS_LONG 14
#define ERROR_USER_NAME_IS_LONG 15

class AccountAdapter {
public:
    enum class PortType {TCP, UDP};

public:
    AccountAdapter();
    AccountAdapter(const RpcGtAc* other);
    ~AccountAdapter();
    // Client Option
    int      setAccountName(const QString& accountName);
    int      setHostName(const QString& hostName);
    void     setPort(unsigned short port, PortType pType = PortType::TCP);
    int      setHubName(const QString& hubName);
    int      setDeviceName(const QString& deviceName);
    QString  getAccountName() const;
    QString  getHostName() const;
    uint     getPort() const;
    PortType getPortType() const;
    QString  getHubName() const;
    QString  getDeviceName() const;

    // Client Auth
    void     setAuthType(AuthType type);
    int      setUserName(const QString& userName);
    int      setPassword(const QString& pass);
    AuthType getAuthType() const;
    QString  getUserName() const;
    QString  getPassword() const;
    RpcCrAc* getRpcClientCreateAccount();

private:
    void alloc();
    void free();
    void init();
    static void copy(RpcCrAc* dest, const RpcGtAc* src);

private:
    RpcCrAc* _account;
};

#endif // ACCOUNTADAPTER_H
