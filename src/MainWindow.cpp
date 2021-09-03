#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), _ui(new Ui::MainWindow),
    _cMenuVpnAcc(NULL), _cMenuNics(NULL) {
    _ui->setupUi(this);
    initPolicy();
    initAccItems();
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
