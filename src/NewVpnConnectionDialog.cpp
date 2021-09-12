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
    _ui->comboBoxAuthType->addItem("Standart Password Authentication");
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
    auto settingName = _ui->lineEditSettingName->text();
    auto hostName = _ui->lineEditHostName->text();
    auto port = _ui->comboBoxPortNumber->currentText();
    auto nubName = _ui->comboBoxHubName->currentText();
    auto nic = _ui->listWidgetNics->currentItem()->text();
    auto userName = _ui->lineEditUserName->text();
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

    // Check Setting Name
    auto settingName = _ui->lineEditSettingName->text();
    if (settingName.isEmpty()) {
        buttonOk->setDisabled(true);
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

AuthType NewVpnConnectionDialog::getAuthType() {
    auto nicRow = _ui->comboBoxAuthType->currentIndex();
    return AuthType(nicRow);
}

void NewVpnConnectionDialog::removeAuth() {
    auto layout = _ui->gridLayoutUpdate->layout();
    while (QLayoutItem* item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
}

void NewVpnConnectionDialog::setAnonimousAuth() {
    removeAuth();
    auto horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    _ui->gridLayoutUpdate->addItem(horizontalSpacer, 1, 0, 1, 1);
}

void NewVpnConnectionDialog::setStandartAuth() {
    removeAuth();
    auto gridLayoutUpdate = new QGridLayout();
    gridLayoutUpdate->setSpacing(3);
    gridLayoutUpdate->setObjectName(QString::fromUtf8("gridLayoutUpdate"));

    auto labelPassword = new QLabel(_ui->groupBox_5);
    labelPassword->setObjectName(QString::fromUtf8("labelPassword"));
    labelPassword->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    gridLayoutUpdate->addWidget(labelPassword, 0, 1, 1, 1);

    auto pushButtonChangePassword = new QPushButton(_ui->groupBox_5);
    pushButtonChangePassword->setObjectName(QString::fromUtf8("pushButtonChangePassword"));

    gridLayoutUpdate->addWidget(pushButtonChangePassword, 2, 3, 1, 1);
    auto lineEditPassword = new QLineEdit(_ui->groupBox_5);
    lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));

    gridLayoutUpdate->addWidget(lineEditPassword, 0, 2, 1, 2);

    auto label = new QLabel(_ui->groupBox_5);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    gridLayoutUpdate->addWidget(label, 1, 1, 1, 3);

    auto horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayoutUpdate->addItem(horizontalSpacer, 1, 0, 1, 1);

    gridLayoutUpdate->setRowStretch(0, 1);
    gridLayoutUpdate->setRowStretch(1, 1);
    gridLayoutUpdate->setRowStretch(2, 1);
    gridLayoutUpdate->setColumnStretch(0, 2);
    gridLayoutUpdate->setColumnStretch(1, 4);
    gridLayoutUpdate->setColumnStretch(2, 5);
    gridLayoutUpdate->setColumnStretch(3, 5);

    _ui->verticalLayout_3->addLayout(gridLayoutUpdate);

    _ui->verticalLayout_3->setStretch(0, 1);
    _ui->verticalLayout_3->setStretch(1, 1);

    _ui->verticalLayoutRight->addWidget(_ui->groupBox_5);
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
