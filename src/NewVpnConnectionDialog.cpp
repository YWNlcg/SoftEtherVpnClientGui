#include "NewVpnConnectionDialog.h"
#include "ui_NewVpnConnectionDialog.h"

NewVpnConnectionDialog::NewVpnConnectionDialog(QWidget *parent) :
    QDialog(parent), _ui(new Ui::NewVpnConnectionDialog) {
    _ui->setupUi(this);
    init();
}

NewVpnConnectionDialog::~NewVpnConnectionDialog() {
    delete _ui;
}

void NewVpnConnectionDialog::setAccountData(const RpcGetAccount *ac) {

}

void NewVpnConnectionDialog::init() {
    auto& cmdAdapter = GetCmdAdapterInstance();

    // Default Setting Name
    QString defName = "New Vpn Connection";
    QString pattern = defName + " (%1)";
    for (int i = 2; !checkSettingName(defName) && i != INT_MAX; ++i) {
        defName = pattern.arg(i);
    }
    _ui->lineEditSettingName->setText(defName);

    // Default ports
    _ui->comboBoxPortNumber->addItem("8888");
    _ui->comboBoxPortNumber->addItem("443");
    _ui->comboBoxPortNumber->addItem("992");
    _ui->comboBoxPortNumber->addItem("5555");

    // Virtual Network Adapters
    QVector<Nic> nicList;
    cmdAdapter.getListNic(nicList);
    for (auto nic: nicList) {
        _ui->listWidgetNics->addItem(nic._deviceName);
    }

    // Default Auth Type
    _ui->comboBoxAuthType->addItem("Anonymous Authentication");
    _ui->comboBoxAuthType->addItem("Standart PAssword Authentication");
    _ui->comboBoxAuthType->addItem("RADIUS or NT Domain Authentication");
    _ui->comboBoxAuthType->addItem("Client Certificate Authentication");
    _ui->comboBoxAuthType->addItem("Smart Card Authentication");

    // Button box - "Cancel", "Ok"
    connect(_ui->buttonBox, &QDialogButtonBox::clicked,
            this, &NewVpnConnectionDialog::onButtonBoxClicked);
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

void NewVpnConnectionDialog::createAccount() {

}

void NewVpnConnectionDialog::onButtonBoxClicked(QAbstractButton *button) {
    if (_ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok) {
        createAccount();
    }
    else if (_ui->buttonBox->standardButton(button) == QDialogButtonBox::Cancel) {
        close();
    }
    else {
        qDebug() << "NewVpnConnectionDialog::slotButtonBox - unknow button is click";
    }
}
