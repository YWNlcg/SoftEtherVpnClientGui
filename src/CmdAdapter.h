#ifndef CMDADAPTER_H
#define CMDADAPTER_H

#include "CTypes.h"
#include "Types.h"
#include "VpnClient.h"
#include "LogHandler.h"


using RpcConStatus = RPC_CLIENT_GET_CONNECTION_STATUS;
using RpcGetAccount = RPC_CLIENT_GET_ACCOUNT;

class CmdAdapter {
public:
    CmdAdapter();
    CmdAdapter(VpnClient* vpnClient);
    CmdAdapter(CmdAdapter&& other);
    CmdAdapter(const CmdAdapter& other);
    const CmdAdapter& operator = (CmdAdapter&& other);
    void init(VpnClient* vpnClient);
    int createNic(const QString& nicName);
    int deleteNic(const QString& nicName);
    int disableNic(const QString& nicName);
    int enableNic(const QString& nicName);
//    QVector<Nic> getListNic();
    int getListNic(QVector<Nic>& nics);
//    int createAccount(AccountAdapter& acAdapter);
//    int setAccount(AccountAdapter& acAdapter);
    int deleteAccount(const QString& accountName);
    int getAccountList(QVector<AccountData>& account);
    int getAccount(const QString& name, RpcGetAccount* account);
    int getConnectionStatus(const QString& conName, RpcConStatus* cs);
    int connect(const QString& name);
    int disconnect(const QString& name);

private:
    VpnClient* _vpnClient;
};

#endif // CMDADAPTER_H
