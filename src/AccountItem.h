#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include "IAccountItem.h"
#include "NewVpnConnectionDialog.h"
//#include "Types.h"

class AccountItem : public IAccountItem {
public:
    AccountItem(const AccountData& data);
    // IAccountItem interface
    QString getTitle() const override;
    AccStatus getStatus() const override;
    QString getStatusStr() const override;
    QString getServerHostName() const override;
    QString getVirtualHub() const override;
    QString getNicName() const override;
    void doubleClick(QWidget* parent) override;

private:
    AccountData _data;

};

#endif // ACCOUNTITEM_H
