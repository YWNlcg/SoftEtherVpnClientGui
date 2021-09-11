#include "MainWindow.h"
#include "ui_MainWindow.h"
<<<<<<< HEAD

extern CmdAdapter& GetCmdAdapterInstance();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    init();
=======
#include "Extern.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), _ui(new Ui::MainWindow),
    _cMenuVpnAcc(NULL), _cMenuNics(NULL) {
    _ui->setupUi(this);
    initPolicy();
    initAccItems();
    initAccTable();
    initNicTable();
>>>>>>> restart-project
}

MainWindow::~MainWindow() {
    delete _ui;
<<<<<<< HEAD
}

void MainWindow::closeEvent(QCloseEvent *event) {
//    if (!isEnabled()) {
//        //event->ignore();
//    }
}

void MainWindow::createNic() {
    QString title = "Create New Virtual Network Adapter";
    QString lable = "A new Virtual Adapter will be created on the system";
    bool ok;
    auto nicName = QInputDialog::getText(this, title, lable, QLineEdit::Normal, "VPN", &ok);
    if (ok) {
        auto& cmdAdapter = GetCmdAdapterInstance();
        auto err = cmdAdapter.createNic(nicName);
        if (err != ERR_NO_ERROR) {
            auto msgErr = GetErrorStr(err);
            QMessageBox::critical(this, PROGRAMM_NAME, msgErr);
            return;
        }
        updateTableVirtualAdapters();
    }
}

void MainWindow::deleteNic(const QString& nicName) {
    QString title = "SoftEther VPN Client";
    QString lable = QString("This will delete the Virtual Network Adapter \"%1\".\n"
                            "Do you really want to do this?").arg(nicName);

    auto reply = QMessageBox::question(this, title, lable, QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        auto& cmdAdapter = GetCmdAdapterInstance();
        auto err = cmdAdapter.deleteNic(nicName);
        if (err == ERR_NO_ERROR) {
            updateTableVirtualAdapters();
        }
    }
}

void MainWindow::disableNic(const QString &nicName) {
    auto& cmdAdapter = GetCmdAdapterInstance();
    auto err = cmdAdapter.disableNic(nicName);
    if (err != ERR_NO_ERROR) {
        auto msgErr = GetErrorStr(err);
        QMessageBox::critical(this, PROGRAMM_NAME, msgErr);
        return;
    }
    updateTableVirtualAdapters();
}

void MainWindow::enableNic(const QString &nicName) {
    auto& cmdAdapter = GetCmdAdapterInstance();
    auto err = cmdAdapter.enableNic(nicName);
    if (err != ERR_NO_ERROR) {
        auto msgErr = GetErrorStr(err);
        QMessageBox::critical(this, PROGRAMM_NAME, msgErr);
        return;
    }
    updateTableVirtualAdapters();
}

void MainWindow::connectTo(const QString &name) {
    auto& cmdAdapter = GetCmdAdapterInstance();
    auto err = cmdAdapter.connect(name);
    if (err != ERR_NO_ERROR) {
        auto msgErr = GetErrorStr(err);
        QMessageBox::critical(this, PROGRAMM_NAME, msgErr);
        return;
    }
    updateTableVpnConnection();
}

void MainWindow::disconnectTo(const QString &name) {
    auto& cmdAdapter = GetCmdAdapterInstance();
    auto err = cmdAdapter.disconnect(name);
    if (err != ERR_NO_ERROR) {
        auto msgErr = GetErrorStr(err);
        QMessageBox::critical(this, PROGRAMM_NAME, msgErr);
        return;
    }
    updateTableVpnConnection();
}

void MainWindow::deleteConnection(const QString &name) {
    QString title = "SoftEther VPN Client";
    QString lable = QString("This will delete VPN Connection Setting \"%1\".\n"
                            "Do you really want to do this?").arg(name);

    auto reply = QMessageBox::question(this, title, lable, QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    auto& cmdAdapter = GetCmdAdapterInstance();
    auto err = cmdAdapter.deleteAccount(name);
    if (err != ERR_NO_ERROR) {
        auto msgErr = GetErrorStr(err);
        QMessageBox::critical(this, PROGRAMM_NAME, msgErr);
        return;
    }
    updateTableVpnConnection();
}

void MainWindow::init() {
    initTableVpnConnection();
    initTableVirtualAdapters();
}

void MainWindow::initTableVpnConnection() {
    initVpnConnectios();
    auto& tableConSettings = _ui->TableWidgetVpnConnectionSettings;

    updateTableVpnConnection();

    tableConSettings->resizeColumnsToContents();
    tableConSettings->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableConSettings->setContextMenuPolicy(Qt::CustomContextMenu);
    tableConSettings->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(tableConSettings, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(contextMenuConSettings(const QPoint&)));
    connect(tableConSettings, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(vpnConDoubleClicked(int, int)));
}

void MainWindow::updateTableVpnConnection() {
    auto tableConSettings = _ui->TableWidgetVpnConnectionSettings;
    for (auto i = tableConSettings->rowCount() - 1; i >= 0; --i) {
        tableConSettings->removeRow(i);
    }

    for (auto iter = _vpnCon.begin(); iter != _vpnCon.end(); ++iter) {
        auto num = iter.key();
        auto name = iter.value()->getName();
        auto vpnServerName = iter.value()->getVpnServerName();
        auto virtualHub = iter.value()->getVirtualHub();
        auto nic = iter.value()->getVirtualNetworkAdapter();

        QString status;
        switch (iter.value()->getStatus()) {
        case IVpnConnection::Status::Null: status = "";break;
        case IVpnConnection::Status::Disconnected: status = "Disconnected";break;
        case IVpnConnection::Status::Connected: status = "Connected";break;
        case IVpnConnection::Status::Connecting: status = "Connecting"; break;
        }

        tableConSettings->insertRow(num);
        tableConSettings->setItem(num, 0, new QTableWidgetItem(name));
        tableConSettings->setItem(num, 1, new QTableWidgetItem(status));
        tableConSettings->setItem(num, 2, new QTableWidgetItem(vpnServerName));
        tableConSettings->setItem(num, 3, new QTableWidgetItem(virtualHub));
        tableConSettings->setItem(num, 4, new QTableWidgetItem(nic));
    }
    tableConSettings->resizeColumnsToContents();
}

void MainWindow::initTableVirtualAdapters() {
    auto& tableVirtAdapters = _ui->TableWidgetNicSettings;

    updateTableVirtualAdapters();

    tableVirtAdapters->resizeColumnsToContents();
    tableVirtAdapters->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVirtAdapters->setContextMenuPolicy(Qt::CustomContextMenu);
    tableVirtAdapters->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(tableVirtAdapters, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(contextMenuVirtNetAdapters(const QPoint&)));
}

void MainWindow::updateTableVirtualAdapters() {
    auto& cmdAdapter = GetCmdAdapterInstance();
    auto& tableVirtAdapters = _ui->TableWidgetNicSettings;
    for (auto i = tableVirtAdapters->rowCount() - 1; i >= 0; --i) {
        tableVirtAdapters->removeRow(i);
    }

    auto num = 0;
    QVector<Nic> nicList;
    cmdAdapter.getListNic(nicList);
    for (auto& nic: nicList) {
        tableVirtAdapters->insertRow(num);

        tableVirtAdapters->setItem(num, 0, new QTableWidgetItem(nic._deviceName));
        tableVirtAdapters->setItem(num, 1, new QTableWidgetItem(nic._enable ? "enable" : "disable"));
        tableVirtAdapters->setItem(num, 2, new QTableWidgetItem(nic._mac_address));
        tableVirtAdapters->setItem(num, 3, new QTableWidgetItem(nic._version));

        ++num;
    }
    tableVirtAdapters->resizeColumnsToContents();
}

void MainWindow::initVpnConnectios() {
    auto& cmdAdapter = GetCmdAdapterInstance();
    QVector<VpnConnectionItem> items;
    cmdAdapter.getAccountList(items);

    _vpnCon[0] = new NewVpnConnection("Add VPN Connection", this);

    int num = 1;
    for (auto& item : items) {
        _vpnCon[num] = new VpnConnection(item, this);
        ++num;
    }
}

void MainWindow::freeVpnConnection() {
    for (auto& item: _vpnCon) {
        delete item;
    }
}

void MainWindow::contextMenuVirtNetAdapters(const QPoint &pos) {
    auto contextMenu = new QMenu(this);

    auto newAdapter = new QAction("New Virtual Network Adapter...");
    auto enableAdapter = new QAction("Enable Virtual Network Adapter");
    auto disableAdapter = new QAction("Disable Virtual Network Adapter");
    auto deleteAdapter = new QAction("Delete Virtual Network Adapter");

    contextMenu->addAction(newAdapter);
    contextMenu->addAction(enableAdapter);
    contextMenu->addAction(disableAdapter);
    contextMenu->addAction(deleteAdapter);

    auto selectedItem = _ui->TableWidgetNicSettings->itemAt(pos);
    // Empty area selected
    if (selectedItem == NULL) {
        enableAdapter->setDisabled(true);
        disableAdapter->setDisabled(true);
        deleteAdapter->setDisabled(true);
    }
    else {
        auto curAdapter = _ui->TableWidgetNicSettings->item(selectedItem->row(), 0)->text();
        auto status = _ui->TableWidgetNicSettings->item(selectedItem->row(), 1)->text();
        if (status == "enable") {
            enableAdapter->setDisabled(true);
        }
        else if (status == "disable") {
            disableAdapter->setDisabled(true);
        }
        else {
            qDebug() << "Error status";
        }

        connect(deleteAdapter, &QAction::triggered, this, [&, curAdapter] () {
            deleteNic(curAdapter);
        });
        connect(enableAdapter, &QAction::triggered, this, [&, curAdapter] () {
            enableNic(curAdapter);
        });
        connect(disableAdapter, &QAction::triggered, this, [&, curAdapter] () {
            disableNic(curAdapter);
        });
    }
    connect(newAdapter, SIGNAL(triggered()), this, SLOT(createNic()));

    contextMenu->exec(QCursor::pos());
}

void MainWindow::contextMenuConSettings(const QPoint& pos) {
    auto contextMenu = new QMenu(this);

    auto actionConnect = new QAction("Connect");
    auto actionViewStatus = new QAction("View Status...");
    auto actionDisconnect = new QAction("Disconnect");
    auto actionNewConSettings = new QAction("New VPN Connection Settings...");
    auto actionDelete = new QAction("Delete");
    auto actionUpdate = new QAction("Update");

    contextMenu->addAction(actionConnect);
    contextMenu->addAction(actionViewStatus);
    contextMenu->addAction(actionDisconnect);
    contextMenu->addAction(actionNewConSettings);
    contextMenu->addAction(actionDelete);
    contextMenu->addAction(actionUpdate);

    auto selectedItem = _ui->TableWidgetVpnConnectionSettings->itemAt(pos);
    // Empty area selected
    if (selectedItem == NULL) {
        actionConnect->setDisabled(true);
        actionViewStatus->setDisabled(true);
        actionDisconnect->setDisabled(true);
        actionDelete->setDisabled(true);
    }
    else {
        auto curRow = selectedItem->row();
        qDebug() << "context menu row=" << curRow;
        auto status = _vpnCon[curRow]->getStatus();

        if (status == IVpnConnection::Status::Null) {
            actionConnect->setDisabled(true);
            actionViewStatus->setDisabled(true);
            actionDisconnect->setDisabled(true);
            actionDelete->setDisabled(true);
        }
        else if (status == IVpnConnection::Status::Connected) {
            actionConnect->setDisabled(true);
            actionDelete->setDisabled(true);
        }
        else if (status == IVpnConnection::Status::Connecting) {
            actionConnect->setDisabled(true);
            actionDelete->setDisabled(true);
        }
        else if (status == IVpnConnection::Status::Disconnected) {
            actionDisconnect->setDisabled(true);
        }

        auto settingName = _ui->TableWidgetVpnConnectionSettings->item(curRow, 0)->text();
        qDebug() << "settingName=" << settingName;

        connect(actionConnect, &QAction::triggered, this, [&, settingName] () {
            connectTo(settingName);
        });
        connect(actionDisconnect, &QAction::triggered, this, [&, settingName] () {
            disconnectTo(settingName);
        });
        connect(actionDelete, &QAction::triggered, this, [&, settingName] () {
            deleteConnection(settingName);
        });
    }

    connect(actionNewConSettings, &QAction::triggered, this, [&] () {
        vpnConDoubleClicked(0, 0);
    });
    connect(actionUpdate, &QAction::triggered, this, [&] () {
       updateTableVirtualAdapters();
       updateTableVpnConnection();
    });

    contextMenu->exec(QCursor::pos());
}

void MainWindow::newConWindow(int row, int column) {

}

void MainWindow::vpnConDoubleClicked(int row, int) {
    _vpnCon[row]->openWindow();
    //this->setDisabled(true);
}

=======
    if (_cMenuNics != NULL) {
        delete _cMenuNics;
    }
    if (_cMenuVpnAcc != NULL) {
        delete _cMenuVpnAcc;
    }
    freeAccItems();
}

void MainWindow::setCMenuVpnAcc(IAccountContextMenu *cMenu) {
    _cMenuVpnAcc = cMenu;
    auto& tableVpnCon = _ui->TableWidgetVpnConnectionSettings;
    connect(tableVpnCon, &QTableWidget::customContextMenuRequested,
            this, &MainWindow::execCMenuVpnAcc);
}

void MainWindow::setCMenuNics(INicContextMenu *cMenu) {
    _cMenuNics = cMenu;
    auto& tableNic = _ui->TableWidgetNicSettings;
    connect(tableNic, &QTableWidget::customContextMenuRequested,
            this, &MainWindow::execCMenuNics);
}

void MainWindow::initPolicy() {
    _ui->TableWidgetVpnConnectionSettings->setContextMenuPolicy(Qt::CustomContextMenu);
    _ui->TableWidgetNicSettings->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::initAccItems() {
    _accItems.push_back(new NewAccountItem("Add VPN Connection"));
    updateAccItems();
}

void MainWindow::initAccTable() {
    _ui->TableWidgetVpnConnectionSettings->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->TableWidgetVpnConnectionSettings->setEditTriggers(QAbstractItemView::NoEditTriggers);
    updateAccTable();
    auto& tableVpnCon = _ui->TableWidgetVpnConnectionSettings;
    connect(tableVpnCon, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::doubleClickVpnAcc);
}

void MainWindow::initNicTable() {
    _ui->TableWidgetNicSettings->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->TableWidgetNicSettings->setEditTriggers(QAbstractItemView::NoEditTriggers);
    updateNicTable();
}

void MainWindow::updateAccTable() {
    auto& accTable =  _ui->TableWidgetVpnConnectionSettings;
    while (accTable->rowCount()) {
        accTable->removeRow(0);
    }

    updateAccItems();
    for (int i = 0; i < _accItems.size(); ++i) {
        accTable->insertRow(i);
        accTable->setItem(i, 0, new QTableWidgetItem(_accItems[i]->getTitle()));
        accTable->setItem(i, 1, new QTableWidgetItem(_accItems[i]->getStatusStr()));
        accTable->setItem(i, 2, new QTableWidgetItem(_accItems[i]->getServerHostName()));
        accTable->setItem(i, 3, new QTableWidgetItem(_accItems[i]->getVirtualHub()));
        accTable->setItem(i, 4, new QTableWidgetItem(_accItems[i]->getNicName()));
    }

    _ui->TableWidgetVpnConnectionSettings->resizeColumnsToContents();
}

void MainWindow::updateNicTable() {
    auto& nicTable = _ui->TableWidgetNicSettings;
    while (nicTable->rowCount()) {
        nicTable->removeRow(0);
    }

    updateNicItems();
    for (int i = 0; i < _nicItems.size(); ++i) {
        nicTable->insertRow(i);
        nicTable->setItem(i, 0, new QTableWidgetItem(_nicItems[i]->getTitle()));
        nicTable->setItem(i, 1, new QTableWidgetItem(_nicItems[i]->getStatusStr()));
        nicTable->setItem(i, 2, new QTableWidgetItem(_nicItems[i]->getMacAddr()));
        nicTable->setItem(i, 3, new QTableWidgetItem(_nicItems[i]->getVersion()));
    }

    _ui->TableWidgetNicSettings->resizeColumnsToContents();
}

void MainWindow::updateAccItems() {
    while (_accItems.size() > 1) {
        delete _accItems.back();
        _accItems.pop_back();
    }

    auto items = getAccountItems();
    for (auto item: items) {
        _accItems.push_back(item);
    }
}

void MainWindow::updateNicItems() {
    while (!_nicItems.empty()) {
        delete _nicItems.back();
        _accItems.pop_back();
    }

    _nicItems = getNicItems();
}

AccItems MainWindow::getAccountItems() {
    AccItems items;
    auto& cmdAdapter = GetCmdAdapterInstance();
    QVector<AccountData> accounts;
    cmdAdapter.getAccountList(accounts);

    for (auto& ac: accounts) {
        items.push_back(new AccountItem(ac));
    }
    return items;
}

NicItems MainWindow::getNicItems() {
    NicItems items;
    auto& cmdAdapter = GetCmdAdapterInstance();
    QVector<Nic> nics;
    cmdAdapter.getListNic(nics);

    for (auto& nic: nics) {
        items.push_back(new NicItem(nic));
    }
    return items;
}

void MainWindow::freeAccItems() {
    for (auto ac: _accItems) {
        delete ac;
    }
}

IAccountItem* MainWindow::getAccountItem(const QPoint &pos) {
    auto item = _ui->TableWidgetVpnConnectionSettings->itemAt(pos);
    return getAccountItem(item->row(), item->column());
}

INicItem* MainWindow::getNicItem(const QPoint &pos) {
    auto item = _ui->TableWidgetNicSettings->itemAt(pos);
    return getNicItem(item->row(), item->column());
}

IAccountItem *MainWindow::getAccountItem(int row, int column) {
    auto selectedItem = _ui->TableWidgetVpnConnectionSettings->item(row, column);
    if (selectedItem == NULL) {
        return NULL;
    }
    auto accName = _ui->TableWidgetVpnConnectionSettings->item(selectedItem->row(), 0)->text();
    for (auto& item: _accItems) {
        if (item->getTitle() == accName) {
            return item;
        }
    }
    return NULL;
}

INicItem *MainWindow::getNicItem(int row, int column) {
    auto selectedItem = _ui->TableWidgetNicSettings->item(row, column);
    if (selectedItem == NULL) {
        return NULL;
    }
    auto accName = _ui->TableWidgetNicSettings->item(selectedItem->row(), 0)->text();
    for (auto& item: _nicItems) {
        if (item->getTitle() == accName) {
            return item;
        }
    }
    return NULL;
}

void MainWindow::execCMenuVpnAcc(const QPoint& pos) {
    qDebug() << "execCMenuVpnAcc";
    auto accountItem = getAccountItem(pos);
    _cMenuVpnAcc->exec(QCursor::pos(), accountItem);
}

void MainWindow::execCMenuNics(const QPoint& pos) {
    qDebug() << "execCMenuNics";
    QString nicName;
    auto nicItem = getNicItem(pos);
    _cMenuNics->exec(QCursor::pos(), nicItem);
}

void MainWindow::doubleClickVpnAcc(int row, int column) {
    auto accountItem = getAccountItem(row, column);
    if (accountItem != NULL) {
        qDebug() << "MainWindow::execCMenuVpnAcc: double click";
        accountItem->doubleClick();
    }
}
>>>>>>> restart-project
