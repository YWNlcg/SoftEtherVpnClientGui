#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), _ui(new Ui::MainWindow),
    _cMenuVpnAcc(NULL), _cMenuNics(NULL) {
    _ui->setupUi(this);
    initPolicy();
}

MainWindow::~MainWindow() {
    delete _ui;
    if (_cMenuNics != NULL) {
        delete _cMenuNics;
    }
    if (_cMenuVpnAcc != NULL) {
        delete _cMenuVpnAcc;
    }
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

void MainWindow::execCMenuVpnAcc(const QPoint&) {
    qDebug() << "execCMenuVpnAcc";
    if (_cMenuVpnAcc != NULL) {
        _cMenuVpnAcc->exec(QCursor::pos());
    }
}

void MainWindow::execCMenuNics(const QPoint&) {
    qDebug() << "execCMenuNics";
    if (_cMenuNics != NULL) {
        _cMenuNics->exec(QCursor::pos());
    }
}

