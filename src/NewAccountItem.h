#ifndef NEWACCOUNTITEM_H
#define NEWACCOUNTITEM_H

#include "AbstractNewAccount.h"

class NewAccountItem : public AbstractNewAccount {
public:
    NewAccountItem(QWidget* parent, const QString& title);
    QString getTitle();
    void doubleClick();

private:
    QString _title;
};

#endif // NEWACCOUNTITEM_H
