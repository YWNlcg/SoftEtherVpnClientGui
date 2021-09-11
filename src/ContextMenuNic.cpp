#include "ContextMenuNic.h"

ContextMenuNic::ContextMenuNic(QWidget* parent)
    : _menu(new QMenu(parent)) {
    _actionNewVNA = new QAction("New Virtual Network Adapter...");
    _actionNewVNA->setObjectName(QString::fromUtf8("actionNewVNA"));

    _actionEnable = new QAction("Enable Virtual Network Adapter");
    _actionEnable->setObjectName(QString::fromUtf8("actionEnable"));

    _actionDisable = new QAction("Disable Virtual Network Adapter");
    _actionDisable->setObjectName(QString::fromUtf8("actionDisable"));

    _actionDelete = new QAction("Delete Virtual Network Adapter");
    _actionDelete ->setObjectName(QString::fromUtf8("actionDelete"));

    _menu->addAction(_actionNewVNA);
    _menu->addAction(_actionEnable);
    _menu->addAction(_actionDisable);
    _menu->addAction(_actionDelete);

    setDisableAll();

    connect(_actionNewVNA, &QAction::triggered, this, &ContextMenuNic::createVNA);
    connect(_actionEnable, &QAction::triggered, this, &ContextMenuNic::enableVNA);
    connect(_actionDisable, &QAction::triggered, this, &ContextMenuNic::disableVNA);
    connect(_actionDelete, &QAction::triggered, this, &ContextMenuNic::deleteVNA);
}

ContextMenuNic::~ContextMenuNic() {
    delete _menu;
}

void ContextMenuNic::exec(const QPoint &pos, INicItem* item) {
    qDebug() << "ContextMenuNic::exec(" << pos << ")";

    if (item != NULL) {
        switch (item->getStatus()) {
        case NicStatus::Enabled: {
            _actionDisable->setEnabled(true);
            _actionDelete->setEnabled(true);
        }; break;

        case NicStatus::Disabled: {
            _actionEnable->setEnabled(true);
            _actionDelete->setEnabled(true);
        }; break;

        default: {
            qDebug() << "NicStatus unknown";
            return;
        }
        }
    }

    _menu->exec(pos);
    setDisableAll();
}

void ContextMenuNic::setDisableAll() {
    _actionEnable->setDisabled(true);
    _actionDisable->setDisabled(true);
    _actionDelete->setDisabled(true);
}

void ContextMenuNic::createVNA() {
    qDebug() << "Create VNA";
}

void ContextMenuNic::enableVNA() {
    qDebug() << "Enable VNA";
}

void ContextMenuNic::disableVNA() {
    qDebug() << "Disable VNA";
}

void ContextMenuNic::deleteVNA() {
    qDebug() << "Delete VNA";
}
