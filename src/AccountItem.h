#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include "IAccountItem.h"
#include "Types.h"

class AccountItem : public IAccountItem {
public:
    AccountItem(const AccountData& data);
    QString getTitle() override;
    Status getStatus() override;
    QString getServerHostName() override;
    QString getVirtualHub() override;
    QString getNicName() override;
    void doubleClick() override;

private:
    AccountData _data;
};

#endif // ACCOUNTITEM_H
