#ifndef IACCOUNTITEM_H
#define IACCOUNTITEM_H

#include <QString>

#include "Types.h"

class IAccountItem {
public:
    virtual ~IAccountItem() {};
    virtual QString getTitle() = 0;
    virtual Status getStatus() = 0;
    virtual QString getStatusStr() = 0;
    virtual QString getServerHostName() = 0;
    virtual QString getVirtualHub() = 0;
    virtual QString getNicName() = 0;
    virtual void doubleClick() = 0;
};

#endif // IACCOUNTITEM_H
