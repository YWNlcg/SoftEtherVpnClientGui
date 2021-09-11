#ifndef NEWACCOUNTITEM_H
#define NEWACCOUNTITEM_H

#include "AbstractNewAccount.h"
#include "NewVpnConnectionDialog.h"

class NewAccountItem : public AbstractNewAccount {
public:
    NewAccountItem(const QString& title);
    QString getTitle() const override;
    void doubleClick(QWidget* parent) override;
private:
    QString _title;
};

#endif // NEWACCOUNTITEM_H
