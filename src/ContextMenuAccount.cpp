#include "ContextMenuAccount.h"
#include "Extern.h"

ContextMenuAccount::ContextMenuAccount(QWidget* parent)
    : _menu(new QMenu(parent)) {
    _actionConnect = new QAction("Connect", _menu);
    _actionConnect->setObjectName(QString::fromUtf8(QOBJ_NAME_ACTION_CONNECT));

    _actionStatus = new QAction("View Status...", _menu);
    _actionStatus->setObjectName(QString::fromUtf8(QOBJ_NAME_ACTION_STATUS));

    _actionDisconnect = new QAction("Disconnect", _menu);
    _actionDisconnect->setObjectName(QString::fromUtf8(QOBJ_NAME_ACTION_DISCONNECT));

    _actionNew = new QAction("New VPN Connection Settings...", _menu);
    _actionNew->setObjectName(QString::fromUtf8(QOBJ_NAME_ACTION_CONNECT));

    _actionDelete = new QAction("Delete", _menu);
    _actionDelete->setObjectName(QString::fromUtf8(QOBJ_NAME_ACTION_DELETE));

    _menu->addAction(_actionConnect);
    _menu->addAction(_actionStatus);
    _menu->addAction(_actionDisconnect);
    _menu->addAction(_actionNew);
    _menu->addAction(_actionDelete);

    setDisableAll();

    connect(_actionNew, &QAction::triggered, this, &ContextMenuAccount::newAccount);
    connect(_actionDelete, &QAction::triggered, this, &ContextMenuAccount::deleteAccount);
    connect(_actionStatus, &QAction::triggered, this, &ContextMenuAccount::statusAccount);
    connect(_actionConnect, &QAction::triggered, this, &ContextMenuAccount::connectAccount);
    connect(_actionDisconnect, &QAction::triggered, this, &ContextMenuAccount::disconnectAccount);
}

ContextMenuAccount::~ContextMenuAccount() {
    qDebug() << "destruct menu";
    delete _menu;
}

void ContextMenuAccount::exec(const QPoint& pos, IAccountItem* item) {
    qDebug() << "ContextMenuAccount::exec(" << pos << ")";
    _item = item;

    if (_item != NULL) {
        switch (item->getStatus()) {
        case Status::Null: {

        }; break;

        case Status::Connected: {
            _actionDisconnect->setEnabled(true);
        }; break;

        case Status::Connecting: {
            _actionDisconnect->setEnabled(true);
        }; break;

        case Status::Offline: {
            _actionDelete->setEnabled(true);
        }; break;

        default: {
            qDebug() << "unknown status";
            return;
        }
        }
    }
    _menu->exec(pos);

    setDisableAll();
}

void ContextMenuAccount::setDisableAll() {
    _actionConnect->setDisabled(true);
    _actionDelete->setDisabled(true);
    _actionDisconnect->setDisabled(true);
    _actionStatus->setDisabled(true);
}

void ContextMenuAccount::newAccount() {
    qDebug() << "New Account";
}

void ContextMenuAccount::deleteAccount() {
    qDebug() << "Delete account";
}

void ContextMenuAccount::statusAccount() {
    qDebug() << "Status Account";
}

void ContextMenuAccount::connectAccount() {
    qDebug() << "Connect Account";
}

void ContextMenuAccount::disconnectAccount() {
    qDebug() << "disconnect Account";
}
