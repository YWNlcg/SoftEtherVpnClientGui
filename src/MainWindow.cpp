#include "MainWindow.h"
#include "ui_mainwindow.h"

extern CmdAdapter& GetCmdAdapterInstance();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    Init();
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
    qDebug() << "rtytr";
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

void MainWindow::Init() {
    InitTableVpnConnection();
    InitTableVirtualAdapters();
}

void MainWindow::InitTableVpnConnection() {
    InitVpnConnectios();
    auto& tableConSettings = _ui->TableWidgetVpnConnectionSettings;

    updateTAbleVpnConnection();

    tableConSettings->resizeColumnsToContents();
    tableConSettings->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableConSettings->setContextMenuPolicy(Qt::CustomContextMenu);
    tableConSettings->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(tableConSettings, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ContextMenuConSettings(const QPoint&)));
    connect(tableConSettings, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(VpnConDoubleClicked(int, int)));
}

void MainWindow::updateTAbleVpnConnection() {
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
}

void MainWindow::InitTableVirtualAdapters() {
    auto& tableVirtAdapters = _ui->TableWidgetNicSettings;

    updateTableVirtualAdapters();

    tableVirtAdapters->resizeColumnsToContents();
    tableVirtAdapters->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableVirtAdapters->setContextMenuPolicy(Qt::CustomContextMenu);
    tableVirtAdapters->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(tableVirtAdapters, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ContextMenuVirtNetAdapters(const QPoint&)));
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
}

void MainWindow::InitVpnConnectios() {
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

void MainWindow::FreeVpnConnection() {
    for (auto& item: _vpnCon) {
        delete item;
    }
}

void MainWindow::ContextMenuVirtNetAdapters(const QPoint &pos) {
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

void MainWindow::ContextMenuConSettings(const QPoint&) {
    auto contextMenu = new QMenu(this);

    auto connect = new QAction("Connect");
    auto viewStatus = new QAction("View Status...");
    auto disconnect = new QAction("Disconnect");
    auto newConSettings = new QAction("New VPN Connection Settings...");

    contextMenu->addAction(connect);
    contextMenu->addAction(viewStatus);
    contextMenu->addAction(disconnect);
    contextMenu->addAction(newConSettings);

    contextMenu->exec(QCursor::pos());
}

void MainWindow::NewConWindow(int row, int column) {

}

void MainWindow::VpnConDoubleClicked(int row, int) {
    _vpnCon[row]->openWindow();
    //this->setDisabled(true);
}

