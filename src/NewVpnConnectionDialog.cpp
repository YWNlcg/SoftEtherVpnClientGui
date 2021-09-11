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

    // For Data Validation
    connect(_ui->lineEditSettingName, &QLineEdit::textEdited,
            this, [&] (const QString &) { dataValidation(); });
    connect(_ui->lineEditHostName, &QLineEdit::textEdited,
            this, [&] (const QString &) { dataValidation(); });
    connect(_ui->comboBoxPortNumber, &QComboBox::currentTextChanged,
            this, [&] (const QString &) { dataValidation(); });
    connect(_ui->comboBoxHubName, &QComboBox::currentTextChanged,
            this, [&] (const QString &) { dataValidation(); });
    connect(_ui->lineEditUserName, &QLineEdit::textEdited,
            this, [&] (const QString &) { dataValidation(); });
    connect(_ui->listWidgetNics, &QListWidget::itemClicked,
            this, [&] (QListWidgetItem*) { dataValidation(); });

    // Disable button - "Ok"
    dataValidation();
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

void NewVpnConnectionDialog::dataValidation() {
    QAbstractButton* buttonOk = NULL;
    auto buttons = _ui->buttonBox->buttons();
    for (auto& button: buttons) {
        if (_ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok) {
            buttonOk = button;
        }
    }
    if (buttonOk == NULL) {
        qDebug() << "NewVpnConnectionDialog::dataValidation - Button \"OK\" not found";
        return;
    }

    // Check HostName
    auto hostName = _ui->lineEditHostName->text();
    if (hostName.isEmpty()) {
        buttonOk->setDisabled(true);
        return;
    }

    // Check Port Number
    auto portStr = _ui->comboBoxPortNumber->currentText();
    bool ok;
    int port = portStr.toUInt(&ok);
    if (!(ok && port > 0 && port <= UINT16_MAX)) {
        buttonOk->setDisabled(true);
        return;
    }

    // Check Virtual NubName
    auto hubName = _ui->comboBoxHubName->currentText();
    if (hubName.isEmpty()) {
        buttonOk->setDisabled(true);
        return;
    }

    // Check Virtual Adapter
    auto currentNic = _ui->listWidgetNics->currentRow();
    if (currentNic == -1) {
        buttonOk->setDisabled(true);
        return;
    }

    // Check User Name
    auto userName = _ui->lineEditUserName->text();
    if (userName.isEmpty()) {
        buttonOk->setDisabled(true);
        return;
    }

    buttonOk->setEnabled(true);
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
