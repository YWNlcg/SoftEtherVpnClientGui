#ifndef NEWACCOUNTITEM_H
#define NEWACCOUNTITEM_H

#include "AbstractNewAccount.h"

class NewAccountItem : public AbstractNewAccount {
public:
    NewAccountItem(const QString& title);
    QString getTitle() override;
    void doubleClick() override;

private:
    QString _title;
};

#endif // NEWACCOUNTITEM_H
