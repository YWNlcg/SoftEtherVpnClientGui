#include "ContextMenuAccount.h"
#include "Extern.h"

ContextMenuAccount::ContextMenuAccount(QWidget* parent)
    : _menu(new QMenu(parent)) {
    logInfo(Widget, "Create context menu for accounts");

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
    logDebug(Widget, "Destruct context menu for account");
    delete _menu;
}

void ContextMenuAccount::exec(const QPoint& pos, IAccountItem* item) {
    logInfo(Widget, "Exec context menu for accounts");
    _item = item;

    if (_item != NULL) {
        switch (item->getStatus()) {
        case AccStatus::Null: {

        }; break;

        case AccStatus::Connected: {
            _actionDisconnect->setEnabled(true);
        }; break;

        case AccStatus::Connecting: {
            _actionDisconnect->setEnabled(true);
        }; break;

        case AccStatus::Offline: {
            _actionConnect->setEnabled(true);
            _actionDelete->setEnabled(true);
        }; break;

        default: {
            logWarning(Widget, "Unknow status: %d", int(item->getStatus()));
            return;
        }
        }
    }
    _menu->exec(pos);

    setDisableAll();
    logDebug(Widget, "Close context menu for accounts");
}

void ContextMenuAccount::setDisableAll() {
    logDebug(Widget, "Disable all context menu");
    _actionConnect->setDisabled(true);
    _actionDelete->setDisabled(true);
    _actionDisconnect->setDisabled(true);
    _actionStatus->setDisabled(true);
}

void ContextMenuAccount::newAccount() {
    logDebug(Widget, "Button pressed - \"Create New Account\"");
}

void ContextMenuAccount::deleteAccount() {
    logDebug(Widget, "Button pressed - \"Delete\"");
}

void ContextMenuAccount::statusAccount() {
    logDebug(Widget, "Button pressed - \"Status\"");
}

void ContextMenuAccount::connectAccount() {
    logDebug(Widget, "Button pressed - \"Connect\"");
    auto& cmdAdapter = GetCmdAdapterInstance();
    auto err = cmdAdapter.connect(_item->getTitle());
    if (err != ERR_NO_ERROR) {
        QMessageBox::critical(_menu, PROGRAMM_NAME, GetErrorStr(err));
    }
}

void ContextMenuAccount::disconnectAccount() {
    logDebug(Widget, "Button pressed - \"Disconnect\"");
}
