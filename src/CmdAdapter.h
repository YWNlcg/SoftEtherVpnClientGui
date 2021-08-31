#ifndef CMDADAPTER_H
#define CMDADAPTER_H

#include "CTypes.h"
#include "Types.h"
#include "VpnClient.h"
#include "AccountAdapter.h"

using AccountItem = RPC_CLIENT_ENUM_ACCOUNT_ITEM;

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
    QVector<Nic> getListNic();
    int getListNic(QVector<Nic>& nics);
    int createAccount(AccountAdapter& acAdapter);
    int setAccount(AccountAdapter& acAdapter);
    int deleteAccount(const QString& accountName);
    int getAccountList(QVector<VpnConnectionItem>& account);
    int getConnectionStatus(const QString& conName);

private:
    VpnClient* _vpnClient;
};

#endif // CMDADAPTER_H
