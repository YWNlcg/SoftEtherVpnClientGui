#ifndef ABSTRACTNEWACCOUNT_H
#define ABSTRACTNEWACCOUNT_H

#include "ITableAccountItem.h"

class AbstractNewAccount : public ITableAccountItem {
public:
    virtual Status getStatus();
    virtual QString getServerHostName();
    virtual QString getVirtualHub();
    virtual QString getNicName();
};

#endif // ABSTRACTNEWACCOUNT_H
