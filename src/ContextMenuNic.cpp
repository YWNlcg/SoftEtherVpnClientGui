#include "ContextMenuNic.h"

ContextMenuNic::ContextMenuNic(QWidget* parent)
    : _menu(new QMenu(parent)) {
    _menu->addAction(new QAction("Connect"));
    _menu->addAction(new QAction("View Status..."));
    _menu->addAction(new QAction("Disconnect"));
    _menu->addAction(new QAction("New VPN Connection Settings..."));
    _menu->addAction(new QAction("Delete"));
    _menu->addAction(new QAction("Update"));
}

ContextMenuNic::~ContextMenuNic() {
    delete _menu;
}

void ContextMenuNic::exec(const QPoint &pos) {
    qDebug() << "ContextMenuNic::exec";
    _menu->exec(pos);
}
