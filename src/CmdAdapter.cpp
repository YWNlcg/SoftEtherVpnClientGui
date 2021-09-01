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
    RPC_CLIENT_CREATE_VLAN t;
    strcpy(t.DeviceName, nicName.toStdString().c_str());
    return CcCreateVLan(_vpnClient->getRemoteClient(), &t);
}

int CmdAdapter::deleteNic(const QString& nicName) {
    RPC_CLIENT_CREATE_VLAN t;
    strcpy(t.DeviceName, nicName.toStdString().c_str());
    return CcDeleteVLan(_vpnClient->getRemoteClient(), &t);
}

int CmdAdapter::disableNic(const QString &nicName) {
    RPC_CLIENT_CREATE_VLAN t;
    strcpy(t.DeviceName, nicName.toStdString().c_str());
    return CcDisableVLan(_vpnClient->getRemoteClient(), &t);
}

int CmdAdapter::enableNic(const QString &nicName) {
    RPC_CLIENT_CREATE_VLAN t;
    strcpy(t.DeviceName, nicName.toStdString().c_str());
    return CcEnableVLan(_vpnClient->getRemoteClient(), &t);
}

int CmdAdapter::getListNic(QVector<Nic> &listNic) {
    RPC_CLIENT_ENUM_VLAN enumVlan;
    Zero(&enumVlan, sizeof(enumVlan));
    auto err = CcEnumVLan(_vpnClient->getRemoteClient(), &enumVlan);

    for (uint i = 0; i < enumVlan.NumItem; ++i) {
        listNic.push_back({
                                enumVlan.Items[i]->DeviceName,
                                enumVlan.Items[i]->Enabled,
                                enumVlan.Items[i]->MacAddress,
                                enumVlan.Items[i]->Version
                            });
    }
    CiFreeClientEnumVLan(&enumVlan);
    return err;
}

int CmdAdapter::createAccount(AccountAdapter &acAdapter) {
    return CcCreateAccount(_vpnClient->getRemoteClient(),
                           acAdapter.getRpcClientCreateAccount());
}

int CmdAdapter::setAccount(AccountAdapter &acAdapter) {
    return CcSetAccount(_vpnClient->getRemoteClient(),
                        acAdapter.getRpcClientCreateAccount());
}

int CmdAdapter::deleteAccount(const QString &accountName) {
    RPC_CLIENT_DELETE_ACCOUNT t;
    auto acNameLen = accountName.size() > MAX_ACCOUNT_NAME_LEN ? MAX_ACCOUNT_NAME_LEN : accountName.size();
    wcsncpy(t.AccountName, accountName.toStdWString().c_str(), acNameLen);
    return CcDeleteAccount(_vpnClient->getRemoteClient(), &t);
}

int CmdAdapter::getAccountList(QVector<VpnConnectionItem> &items) {
    RPC_CLIENT_ENUM_ACCOUNT t;
    auto err = CcEnumAccount(_vpnClient->getRemoteClient(), &t);
    for (uint i = 0 ; i < t.NumItem; ++i) {
        items.push_back({
                            QString::fromStdWString(t.Items[i]->AccountName),
                            t.Items[i]->Connected,
                            t.Items[i]->ServerName,
                            t.Items[i]->HubName,
                            t.Items[i]->DeviceName
                        });
    }
    CiFreeClientEnumAccount(&t);
    return err;
}

int CmdAdapter::getConnectionStatus(const QString &conName) {

}
