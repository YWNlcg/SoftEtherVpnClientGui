#include "ContextMenuNic.h"

ContextMenuNic::ContextMenuNic(QWidget* parent)
    : _menu(new QMenu(parent)) {
    auto actionNewVNA = new QAction("New Virtual Network Adapter...");
    actionNewVNA->setObjectName(QString::fromUtf8("actionNewVNA"));
    actionNewVNA->setDisabled(true);

    auto actionEnable = new QAction("Enable Virtual Network Adapter");
    actionEnable->setObjectName(QString::fromUtf8("actionEnable"));
    actionEnable->setDisabled(true);

    auto actionDisable = new QAction("Disable Virtual Network Adapter");
    actionDisable->setObjectName(QString::fromUtf8("actionDisable"));
    actionDisable->setDisabled(true);

    auto actionDelete = new QAction("Delete Virtual Network Adapter");
    actionDelete ->setObjectName(QString::fromUtf8("actionDelete"));
    actionDelete ->setDisabled(true);

    _menu->addAction(actionNewVNA);
    _menu->addAction(actionEnable);
    _menu->addAction(actionDisable);
    _menu->addAction(actionDelete);
}

ContextMenuNic::~ContextMenuNic() {
    delete _menu;
}

void ContextMenuNic::exec(const QPoint &pos, const INicItem* item) {
    qDebug() << "ContextMenuNic::exec(" << pos << ")";
    _menu->exec(pos);
}
