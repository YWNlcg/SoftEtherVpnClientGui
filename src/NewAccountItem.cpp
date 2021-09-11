#include "NewAccountItem.h"

NewAccountItem::NewAccountItem(const QString &title)
    : _title(title) {

}

QString NewAccountItem::getTitle() const {
    return _title;
}

void NewAccountItem::doubleClick(QWidget* parent) {
    qDebug() << parent;
}



