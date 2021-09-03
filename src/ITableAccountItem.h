#ifndef ITABLEACCOUNTITEM_H
#define ITABLEACCOUNTITEM_H

#include <QString>

#include "Types.h"

class ITableAccountItem {
public:
    virtual ~ITableAccountItem() {};
    virtual QString getTitle() = 0;
    virtual Status getStatus() = 0;
    virtual QString getServerHostName() = 0;
    virtual QString getVirtualHub() = 0;
    virtual QString getNicName() = 0;
    virtual void doubleClick() = 0;
};

#endif // ITABLEACCOUNTITEM_H
