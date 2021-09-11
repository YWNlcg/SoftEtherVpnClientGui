#include "NewVpnConnectionDialog.h"
#include "ui_NewVpnConnectionDialog.h"

NewVpnConnectionDialog::NewVpnConnectionDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewVpnConnectionDialog) {
    _ui->setupUi(this);
}

NewVpnConnectionDialog::~NewVpnConnectionDialog() {
    delete _ui;
}

void NewVpnConnectionDialog::init() {

}

bool NewVpnConnectionDialog::checkSettingName(const QString &name) {
    auto& cmdAdapter = GetCmdAdapterInstance();

    QVector<AccountData> accounts;
    cmdAdapter.getAccountList(accounts);

    for (auto acc: accounts) {
        if (acc._vpnConName == name) {
            return false;
        }
    }
    return true;
}
