#include "CmdAdapter.h"

CmdAdapter::CmdAdapter() : CmdAdapter(NULL) {cout << "3\n";}

CmdAdapter::CmdAdapter(VpnClient *vpnClient)
    : _vpnClient(vpnClient) {}

CmdAdapter::CmdAdapter(CmdAdapter &&other)
    : CmdAdapter(other._vpnClient) {
}

CmdAdapter::CmdAdapter(const CmdAdapter &other)
    : CmdAdapter(other._vpnClient) {
}

const CmdAdapter &CmdAdapter::operator =(CmdAdapter &&other) {
    _vpnClient = other._vpnClient;
    return *this;
}

void CmdAdapter::init(VpnClient *vpnClient) {
    _vpnClient = vpnClient;
}

int CmdAdapter::createNic(const QString& nicName) {
    RPC_CLIENT_CREATE_VLAN *t = new RPC_CLIENT_CREATE_VLAN;
    Zero(t, sizeof(RPC_CLIENT_CREATE_VLAN));
    strcpy(t->DeviceName, nicName.toStdString().c_str());
    auto ret = CcCreateVLan(_vpnClient->getRemoteClient(), t);
    delete t;
    return  ret;
}

int CmdAdapter::deleteNic(const QString& nicName) {
    RPC_CLIENT_CREATE_VLAN *t = new RPC_CLIENT_CREATE_VLAN;
    Zero(t, sizeof(RPC_CLIENT_CREATE_VLAN));
    strcpy(t->DeviceName, nicName.toStdString().c_str());
    auto ret = CcDeleteVLan(_vpnClient->getRemoteClient(), t);
    delete t;
    return ret;
}

int CmdAdapter::disableNic(const QString &nicName) {
    RPC_CLIENT_CREATE_VLAN *t = new RPC_CLIENT_CREATE_VLAN;
    Zero(t, sizeof(RPC_CLIENT_CREATE_VLAN));
    strcpy(t->DeviceName, nicName.toStdString().c_str());
    auto ret = CcDisableVLan(_vpnClient->getRemoteClient(), t);
    delete t;
    return ret;
}

int CmdAdapter::enableNic(const QString &nicName) {
    RPC_CLIENT_CREATE_VLAN *t = new RPC_CLIENT_CREATE_VLAN;
    Zero(t, sizeof(RPC_CLIENT_CREATE_VLAN));
    strcpy(t->DeviceName, nicName.toStdString().c_str());
    auto ret = CcEnableVLan(_vpnClient->getRemoteClient(), t);
    delete t;
    return ret;
}

int CmdAdapter::getListNic(QVector<Nic> &listNic) {
    RPC_CLIENT_ENUM_VLAN *enumVlan = new RPC_CLIENT_ENUM_VLAN;
    //Zero(&enumVlan, sizeof(RPC_CLIENT_ENUM_VLAN));
    auto err = CcEnumVLan(_vpnClient->getRemoteClient(), enumVlan);

    for (uint i = 0; i < enumVlan->NumItem; ++i) {
        listNic.push_back({
                                enumVlan->Items[i]->DeviceName,
                                enumVlan->Items[i]->Enabled,
                                enumVlan->Items[i]->MacAddress,
                                enumVlan->Items[i]->Version
                            });
    }
    CiFreeClientEnumVLan(enumVlan);
    delete enumVlan;
    return err;
}

//int CmdAdapter::createAccount(AccountAdapter &acAdapter) {
//    return CcCreateAccount(_vpnClient->getRemoteClient(),
//                           acAdapter.getRpcClientCreateAccount());
//}

//int CmdAdapter::setAccount(AccountAdapter &acAdapter) {
//    return CcSetAccount(_vpnClient->getRemoteClient(),
//                        acAdapter.getRpcClientCreateAccount());
//}

int CmdAdapter::deleteAccount(const QString &accountName) {
    RPC_CLIENT_DELETE_ACCOUNT *t = new RPC_CLIENT_DELETE_ACCOUNT;
    Zero(t, sizeof(RPC_CLIENT_DELETE_ACCOUNT));
    auto acNameLen = accountName.size() > MAX_ACCOUNT_NAME_LEN ? MAX_ACCOUNT_NAME_LEN : accountName.size();
    wcsncpy(t->AccountName, accountName.toStdWString().c_str(), acNameLen);
    auto ret = CcDeleteAccount(_vpnClient->getRemoteClient(), t);
    delete t;
    return ret;
}

int CmdAdapter::getAccountList(QVector<VpnConnectionItem> &items) {
    RPC_CLIENT_ENUM_ACCOUNT *t = new RPC_CLIENT_ENUM_ACCOUNT;
    auto err = CcEnumAccount(_vpnClient->getRemoteClient(), t);
    for (uint i = 0 ; i < t->NumItem; ++i) {
        items.push_back({
                            QString::fromStdWString(t->Items[i]->AccountName),
                            t->Items[i]->Active,
                            t->Items[i]->Connected,
                            t->Items[i]->ServerName,
                            t->Items[i]->HubName,
                            t->Items[i]->DeviceName
                        });
    }
    CiFreeClientEnumAccount(t);
    delete t;
    return err;
}

int CmdAdapter::getConnectionStatus(const QString &conName) {

}

int CmdAdapter::connect(const QString &name) {
    RPC_CLIENT_CONNECT *t = new RPC_CLIENT_CONNECT;
    Zero(t, sizeof(RPC_CLIENT_CONNECT));
    wcsncpy(t->AccountName, name.toStdWString().c_str(), name.size());
    auto ret = CcConnect(_vpnClient->getRemoteClient(), t);
    delete t;
    return ret;
}

int CmdAdapter::disconnect(const QString &name) {
    RPC_CLIENT_CONNECT *t = new RPC_CLIENT_CONNECT;
    Zero(t, sizeof(RPC_CLIENT_CONNECT));
    wcsncpy(t->AccountName, name.toStdWString().c_str(), name.size());
    auto ret = CcDisconnect(_vpnClient->getRemoteClient(), t);
    delete t;
    return ret;
}
