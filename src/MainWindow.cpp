#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), _ui(new Ui::MainWindow),
    _cMenuVpnAcc(NULL), _cMenuNics(NULL) {
    _ui->setupUi(this);
    initPolicy();
    initAccItems();
    initAccTable();
    initNicTable();
}

MainWindow::~MainWindow() {
    delete _ui;
    if (_cMenuNics != NULL) {
        delete _cMenuNics;
    }
    if (_cMenuVpnAcc != NULL) {
        delete _cMenuVpnAcc;
    }
    freeAccItems();
}

void MainWindow::setCMenuVpnAcc(IContextMenu *cMenu) {
    _cMenuVpnAcc = cMenu;
    auto& tableVpnCon = _ui->TableWidgetVpnConnectionSettings;
    connect(tableVpnCon, &QTableWidget::customContextMenuRequested,
            this, &MainWindow::execCMenuVpnAcc);
}

void MainWindow::setCMenuNics(IContextMenu *cMenu) {
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

void MainWindow::freeAccItems() {
    for (auto ac: _accItems) {
        delete ac;
    }
}

void MainWindow::execCMenuVpnAcc(const QPoint&) {
    qDebug() << "execCMenuVpnAcc";
    if (_cMenuVpnAcc != NULL) {
        _cMenuVpnAcc->exec(QCursor::pos());
    }
}

void MainWindow::execCMenuNics(const QPoint& pos) {
    qDebug() << "execCMenuNics";
    QString nicName;
    auto selectedItem = _ui->TableWidgetNicSettings->itemAt(pos);
    if (selectedItem != NULL) {
        nicName = _ui->TableWidgetNicSettings->item(selectedItem->row(), 0)->text();
    }

    if (_cMenuNics != NULL) {
        _cMenuNics->exec(QCursor::pos(), nicName);
    }
}
