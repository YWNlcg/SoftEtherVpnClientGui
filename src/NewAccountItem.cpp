#include "NewAccountItem.h"

NewAccountItem::NewAccountItem(const QString &title)
    : _title(title) {
    logInfo(Widget, "Create New Account Item: %s", title.toStdString().c_str());
}

QString NewAccountItem::getTitle() const {
    return _title;
}

void NewAccountItem::doubleClick(QWidget* parent) {
    logInfo(Widget, "Double click on NewAccountItem");
    NewVpnConnectionDialog dialog(parent);
    dialog.exec();
}



