#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include "ITableAccountItem.h"
#include "Types.h"

class AccountItem : public ITableAccountItem {
public:
    AccountItem(QWidget* parent, const AccountData& data);
    QString getTitle();
    Status getStatus();
    QString getServerHostName();
    QString getVirtualHub();
    QString getNicName();
    void doubleClick();

private:
    AccountData _data;
};

#endif // ACCOUNTITEM_H
