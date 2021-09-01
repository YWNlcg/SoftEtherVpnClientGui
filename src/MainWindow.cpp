#include "MainWindow.h"
#include "ui_MainWindow.h"

extern CmdAdapter& GetCmdAdapterInstance();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    init();
}

MainWindow::~MainWindow() {
    delete _ui;
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

    contextMenu->addAction(actionConnect);
    contextMenu->addAction(actionViewStatus);
    contextMenu->addAction(actionDisconnect);
    contextMenu->addAction(actionNewConSettings);

    auto selectedItem = _ui->TableWidgetNicSettings->itemAt(pos);
    // Empty area selected
    if (selectedItem == NULL) {
        actionConnect->setDisabled(true);
        actionViewStatus->setDisabled(true);
        actionDisconnect->setDisabled(true);
    }
    else {
        auto curRow = selectedItem->row();
        qDebug() << "context menu row=" << curRow;
        auto status = _vpnCon[curRow]->getStatus();

        if (status == IVpnConnection::Status::Null) {
            actionConnect->setDisabled(true);
            actionViewStatus->setDisabled(true);
            actionDisconnect->setDisabled(true);
        }
        else if (status == IVpnConnection::Status::Connected) {
            actionConnect->setDisabled(true);
        }
        else if (status == IVpnConnection::Status::Disconnected) {
            actionDisconnect->setDisabled(true);
        }

        auto settingName = _ui->TableWidgetNicSettings->item(selectedItem->row(), 0)->text();
        qDebug() << "settingName=" << settingName;

        connect(actionConnect, &QAction::triggered, this, [&, settingName] () {
            connectTo(settingName);
        });
        connect(actionDisconnect, &QAction::triggered, this, [&, settingName] () {
            disconnectTo(settingName);
        });
    }

    connect(actionNewConSettings, &QAction::triggered, this, [&] () {
        vpnConDoubleClicked(0, 0);
    });

    contextMenu->exec(QCursor::pos());
}

void MainWindow::newConWindow(int row, int column) {

}

void MainWindow::vpnConDoubleClicked(int row, int) {
    _vpnCon[row]->openWindow();
    //this->setDisabled(true);
}

