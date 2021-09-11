#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Extern.h"

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
            this, )
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

void MainWindow::execCMenuVpnAcc(int row, int column) {

}
