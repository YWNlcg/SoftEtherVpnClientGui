#include "ContextMenuAccount.h"

ContextMenuAccount::ContextMenuAccount(QWidget* parent)
    : _menu(new QMenu(parent)) {
    _menu->addAction(new QAction("New Virtual Network Adapter..."));
    _menu->addAction(new QAction("Enable Virtual Network Adapter"));
    _menu->addAction(new QAction("Disable Virtual Network Adapter"));
    _menu->addAction(new QAction("Delete Virtual Network Adapter"));
}

ContextMenuAccount::~ContextMenuAccount() {
    delete _menu;
}

void ContextMenuAccount::exec(const QPoint &pos) {
    qDebug() << "ContextMenuAccount::exec";
    _menu->exec(pos);
}
