#include "NewAccountItem.h"

NewAccountItem::NewAccountItem(QWidget *parent, const QString &title)
    : _title(title) {

}

QString NewAccountItem::getTitle() {
    return _title;
}

void NewAccountItem::doubleClick() {

}
