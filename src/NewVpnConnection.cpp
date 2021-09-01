#include "NewVpnConnection.h"
#include "ui_NewVpnConnectionWindow.h"

extern CmdAdapter& GetCmdAdapterInstance();

NewVpnConnection::NewVpnConnection(QString name, QWidget* parent)
    :  QMainWindow(parent), _ui(new Ui::newVpnConSettingWindow), _name(name) {
    _ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    initWindow();
}

QString NewVpnConnection::getName() {
    return _name;
}

IVpnConnection::Status NewVpnConnection::getStatus() {
    return Status::Null;
}

QString NewVpnConnection::getVpnServerName() {
    return QString();
}

QString NewVpnConnection::getVirtualHub() {
    return QString();
}

QString NewVpnConnection::getVirtualNetworkAdapter() {
    return QString();
}

void NewVpnConnection::openWindow() {
    updateListNics();
    show();
}

void NewVpnConnection::initWindow() {
    _ui->comboBoxTypeAuth->addItem("Anonymous Authentication");
    _ui->comboBoxTypeAuth->addItem("Standart Password Authentication");
    _ui->comboBoxTypeAuth->addItem("RADIUS or NT Domain Authentication");
    _ui->comboBoxTypeAuth->addItem("Client Certificate Authentication");
    _ui->comboBoxTypeAuth->addItem("Smart Card Authentication");

    connect(_ui->comboBoxTypeAuth, &QComboBox::currentIndexChanged, this, &NewVpnConnection::updateAuthMethod);
    emit _ui->comboBoxTypeAuth->currentIndexChanged(0);

    connect(_ui->pushButtonOk, &QPushButton::clicked, this, &NewVpnConnection::createNewConnection);
    connect(_ui->pushButtonCancel, &QPushButton::clicked, this, &NewVpnConnection::close);
    connect(_ui->lineEditSettingName, &QLineEdit::textEdited, this, &NewVpnConnection::checkLineEdit);
    connect(_ui->comboBoxPort, &QComboBox::currentTextChanged, this, &NewVpnConnection::checkLineEdit);
    connect(_ui->comboBoxHubName, &QComboBox::currentTextChanged, this, &NewVpnConnection::checkLineEdit);
    connect(_ui->lineEditHostName, &QLineEdit::textEdited, this, &NewVpnConnection::checkLineEdit);
    connect(_ui->listWidgetNic, &QListWidget::currentRowChanged, this, &NewVpnConnection::checkListWidget);
}

void NewVpnConnection::updateListNics() {
    auto& cmdAdapter = GetCmdAdapterInstance();
    QVector<Nic> nicList;
    cmdAdapter.getListNic(nicList);

    for (int i = _ui->listWidgetNic->count() - 1; i >= 0; --i) {
        _ui->listWidgetNic->takeItem(i);
    }

    for (auto iter = nicList.begin(); iter != nicList.end(); ++iter) {
        _ui->listWidgetNic->addItem(iter->_deviceName);
//        qDebug() << iter->_deviceName;
    }
}

void NewVpnConnection::setAnonAuth() {
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _ui->verticalLayoutCustom->addItem(verticalSpacer);
}

void NewVpnConnection::setStandartAuth() {
    QHBoxLayout* horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    horizontalLayout_9->setContentsMargins(60, 0, 50, 0);

    QLabel* labelUserPassword = new QLabel(_ui->groupBoxAdvancedSetting);
    labelUserPassword->setObjectName(QString::fromUtf8("labelUserPassword"));
    labelUserPassword->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    labelUserPassword->setText(QString::fromUtf8("Password"));

    horizontalLayout_9->addWidget(labelUserPassword);

    QLineEdit* lineEditUserPassword = new QLineEdit(_ui->groupBoxAdvancedSetting);
    lineEditUserPassword->setObjectName(QString::fromUtf8("lineEditUserPassword"));

    horizontalLayout_9->addWidget(lineEditUserPassword);

    _ui->verticalLayoutCustom->addLayout(horizontalLayout_9);
//
    QGridLayout* gridLayout_4 = new QGridLayout();
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));

    QPushButton* pushButtonChangePassword = new QPushButton(_ui->groupBoxAdvancedSetting);
    pushButtonChangePassword->setObjectName(QString::fromUtf8("pushButtonChangePassword"));
    pushButtonChangePassword->setText(QString::fromUtf8("Change Password"));

    gridLayout_4->addWidget(pushButtonChangePassword, 1, 1, 1, 1);

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout_4->addItem(horizontalSpacer, 0, 0, 1, 2);

    QLabel* label = new QLabel(_ui->groupBoxAdvancedSetting);
    label->setObjectName(QString::fromUtf8("labelMsg"));
    label->setScaledContents(false);
    label->setAlignment(Qt::AlignCenter);
    label->setText(QString::fromUtf8("You can change the user`s password on the VPN Server"));

    gridLayout_4->addWidget(label, 0, 0, 1, 2);
    gridLayout_4->setColumnStretch(0, 3);
    gridLayout_4->setColumnStretch(1, 2);

    _ui->verticalLayoutCustom->addLayout(gridLayout_4);
}

void NewVpnConnection::setRadiusAuth() {
    QHBoxLayout* horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    horizontalLayout_9->setContentsMargins(60, 0, 50, 0);

    QLabel* labelUserPassword = new QLabel(_ui->groupBoxAdvancedSetting);
    labelUserPassword->setObjectName(QString::fromUtf8("labelUserPassword"));
    labelUserPassword->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    labelUserPassword->setText(QString::fromUtf8("Password"));

    horizontalLayout_9->addWidget(labelUserPassword);

    QLineEdit* lineEditUserPassword = new QLineEdit(_ui->groupBoxAdvancedSetting);
    lineEditUserPassword->setObjectName(QString::fromUtf8("lineEditUserPassword"));

    horizontalLayout_9->addWidget(lineEditUserPassword);

    _ui->verticalLayoutCustom->addLayout(horizontalLayout_9);
//
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _ui->verticalLayoutCustom->addItem(verticalSpacer);
}

void NewVpnConnection::setCertificateAuth() {
    QHBoxLayout* horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    horizontalLayout_9->setSpacing(0);
    horizontalLayout_9->setContentsMargins(0, 0, 0, 0);

    QLabel* labelIcon = new QLabel(_ui->groupBoxAdvancedSetting);
    labelIcon->setObjectName(QString::fromUtf8("labelIcon"));
    labelIcon->setText(QString::fromUtf8("Icon"));

    horizontalLayout_9->addWidget(labelIcon);

    QLabel* labelTitle_5 = new QLabel(_ui->groupBoxAdvancedSetting);
    labelTitle_5->setObjectName(QString::fromUtf8("labelTitle_5"));
    labelTitle_5->setText(QString::fromUtf8("You must specify a client certificate "
                                            "to be used for user\nauthentication"));

    horizontalLayout_9->addWidget(labelTitle_5);
    horizontalLayout_9->setStretch(0, 2);
    horizontalLayout_9->setStretch(1, 7);

    _ui->verticalLayoutCustom->addLayout(horizontalLayout_9);

    QHBoxLayout* horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));

    QPushButton* pushButtonViewCert = new QPushButton(_ui->groupBoxAdvancedSetting);
    pushButtonViewCert->setObjectName(QString::fromUtf8("pushButtonViewCert"));
    pushButtonViewCert->setText(QString::fromUtf8("View Client Certificate"));

    QPushButton* pushButtonSpecifyCert = new QPushButton(_ui->groupBoxAdvancedSetting);
    pushButtonSpecifyCert->setObjectName(QString::fromUtf8("pushButtonSpecifyCert"));
    pushButtonSpecifyCert->setText(QString::fromUtf8("Specify Client Certificate"));

    horizontalLayout_10->addWidget(pushButtonViewCert);
    horizontalLayout_10->addWidget(pushButtonSpecifyCert);

    _ui->verticalLayoutCustom->addLayout(horizontalLayout_10);
}

void NewVpnConnection::setSmartCardAuth() {
    QHBoxLayout* horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    horizontalLayout_9->setSpacing(0);
    horizontalLayout_9->setContentsMargins(0, 0, 0, 0);

    QLabel* labelIcon = new QLabel(_ui->groupBoxAdvancedSetting);
    labelIcon->setObjectName(QString::fromUtf8("labelIcon"));
    labelIcon->setText(QString::fromUtf8("Icon"));

    horizontalLayout_9->addWidget(labelIcon);

    QLabel* labelTitle_6 = new QLabel(_ui->groupBoxAdvancedSetting);
    labelTitle_6->setObjectName(QString::fromUtf8("labelTitle_6"));
    labelTitle_6->setText(QString::fromUtf8("Specify the client certificate and private key inside the\n"
                                            "smart card to be used for user authentication"));

    horizontalLayout_9->addWidget(labelTitle_6);
    horizontalLayout_9->setStretch(0, 2);
    horizontalLayout_9->setStretch(1, 7);

    _ui->verticalLayoutCustom->addLayout(horizontalLayout_9);

    QHBoxLayout* horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10 = new QHBoxLayout();
    horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));

    QPushButton* pushButtonSelectSmartCard = new QPushButton(_ui->groupBoxAdvancedSetting);
    pushButtonSelectSmartCard->setObjectName(QString::fromUtf8("pushButtonSelectSmartCard"));
    pushButtonSelectSmartCard->setText(QString::fromUtf8("Select Smart Card"));

    QPushButton* pushButtonSpecifyCert = new QPushButton(_ui->groupBoxAdvancedSetting);
    pushButtonSpecifyCert->setObjectName(QString::fromUtf8("pushButtonSpecifyCert"));
    pushButtonSpecifyCert->setText(QString::fromUtf8("Specify Cert and Private Key"));

    horizontalLayout_10->addWidget(pushButtonSelectSmartCard);
    horizontalLayout_10->addWidget(pushButtonSpecifyCert);

    _ui->verticalLayoutCustom->addLayout(horizontalLayout_10);
}

void NewVpnConnection::clearAuthType() {
    qDebug() << _ui->verticalLayoutCustom->children();

    while (auto item = _ui->verticalLayoutCustom->itemAt(0)) {
        qDebug() << _ui->verticalLayoutCustom->count();
        qDebug() << item;
        if (item->layout() != NULL) {
            while (auto item2 = item->layout()->itemAt(0)) {
                item->layout()->removeItem(item2);
                delete item2->widget();
            }
        }
        _ui->verticalLayoutCustom->removeItem(item);
        delete item->widget();
        delete item;
    }
}

AuthType NewVpnConnection::getAuthType() {
    AuthType curAuthType;

    auto index = _ui->comboBoxTypeAuth->currentIndex();
    switch (index) {
    case (int)AuthType::Anonymous:   curAuthType = AuthType::Anonymous; break;
    case (int)AuthType::Standart:    curAuthType = AuthType::Standart; break;
    case (int)AuthType::Radius:      curAuthType = AuthType::Radius; break;
    case (int)AuthType::Certificate: curAuthType = AuthType::Certificate; break;
    case (int)AuthType::SecureDevice:curAuthType = AuthType::SecureDevice; break;
    default: curAuthType = AuthType::Unknown; break;
    }
    return curAuthType;
}

void NewVpnConnection::dataCkecking() {
    // Check Setting name
    auto settingName = _ui->lineEditSettingName->text();
    if (settingName.isEmpty()) {
        _ui->pushButtonOk->setDisabled(true);
        return;
    }
    // Check HostName
    auto hostName = _ui->lineEditHostName->text();
    if (hostName.isEmpty()) {
        _ui->pushButtonOk->setDisabled(true);
        return;
    }
    // Check Port number
    bool ok;
    auto portNumber = _ui->comboBoxPort->currentText();
    portNumber.toUInt(&ok);
    if (portNumber.isEmpty() || !ok) {
        _ui->pushButtonOk->setDisabled(true);
        return;
    }
    // Check Nic
    auto currentNic = _ui->listWidgetNic->currentRow();
    if (currentNic == -1) {
        _ui->pushButtonOk->setDisabled(true);
        return;
    }

    // Check User Name
    auto userName = _ui->lineEditUserName->text();
    if (userName.isEmpty()) {
        _ui->pushButtonOk->setDisabled(true);
        return;
    }

    _ui->pushButtonOk->setEnabled(true);
}

void NewVpnConnection::createNewConnection() {
    auto& cmdAdapter = GetCmdAdapterInstance();
    AccountAdapter acAdapter;

    // first configure
    acAdapter.setAccountName(_ui->lineEditSettingName->text());

    // Destination VPN Server
    acAdapter.setHostName(_ui->lineEditHostName->text());
    acAdapter.setPort(_ui->comboBoxPort->currentText().toInt());
    acAdapter.setHubName(_ui->comboBoxHubName->currentText());

    // Proxy Server as Relay

    // Server Certificate Verification Option

    // Virtual Network Adapter to Use
    auto item = _ui->listWidgetNic->currentItem();
    if (item == NULL) {
        QMessageBox::critical(this, PROGRAMM_NAME, "The virtual network adapter is not selected.\n"
                                                   "Please select a virtual network adapter");
        return;
    }

    // User Authentication Setting

    acAdapter.setUserName(_ui->lineEditUserName->text());
    QString userPassword;

    switch (getAuthType()) {
    case AuthType::Anonymous: {
        qDebug() << "AuthType::Anonymous";
    }; break;
    case AuthType::Standart: {
        auto lineEditUserPassword = findChild<QLineEdit*>("lineEditUserPassword");
        if (lineEditUserPassword != NULL) {
            userPassword = lineEditUserPassword->text();
        }
        else {
            qDebug() << "error - password is NULL";
        }
    }; break;
    case AuthType::Radius: {
        auto lineEditUserPassword = findChild<QLineEdit*>("lineEditUserPassword");
        if (lineEditUserPassword != NULL) {
            userPassword = lineEditUserPassword->text();
        }
        else {
            qDebug() << "error - password is NULL";
        }
    }; break;
    case AuthType::Certificate: {
        qDebug() << "AuthType::Certificate not found";
        return;
    }; break;
    case AuthType::SecureDevice: {
        qDebug() << "AuthType::SmartCard not found";
        return;
    }; break;
    default: {
        qDebug() << "AuthType not found";
        QMessageBox::critical(this, PROGRAMM_NAME, "Unknown Authentication type");
        return;
    };
    }

    acAdapter.setPassword(userPassword);
    acAdapter.setAuthType(getAuthType());

    qDebug() << acAdapter;
    auto err = cmdAdapter.createAccount(acAdapter);
    if (err != ERR_NO_ERROR) {
        QMessageBox::critical(this, PROGRAMM_NAME, GetErrorStr(err));
        return;
    }

    close();
}

void NewVpnConnection::updateAuthMethod(int index) {
    clearAuthType();

    switch (index) {
    // Anonymous Authentication
    case (int)AuthType::Anonymous: {
        setAnonAuth();
    }; break;
    // Standart Password Authentication
    case (int)AuthType::Standart: {
        setStandartAuth();
    }; break;
    // RADIUS or NT Domain Authentication
    case (int)AuthType::Radius: {
        setRadiusAuth();
    }; break;
    // Client Certificate Authentication
    case (int)AuthType::Certificate: {
        setCertificateAuth();
    }; break;
    // Smart Card Authentication
    case (int)AuthType::SecureDevice: {
        setSmartCardAuth();
    }; break;
    default: break;
    }
}

void NewVpnConnection::checkLineEdit(const QString &text) {
    dataCkecking();
}

void NewVpnConnection::checkListWidget(int currentRow) {
    dataCkecking();
}

NewVpnConnection::~NewVpnConnection() {
    delete _ui;
}
