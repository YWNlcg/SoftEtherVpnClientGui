#include "NewAccountItem.h"

NewAccountItem::NewAccountItem(const QString &title)
    : _title(title) {

}

QString NewAccountItem::getTitle() {
    return _title;
}

void NewAccountItem::doubleClick() {

}
