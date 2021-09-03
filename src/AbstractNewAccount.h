#ifndef ABSTRACTNEWACCOUNT_H
#define ABSTRACTNEWACCOUNT_H

#include "IAccountItem.h"

class AbstractNewAccount : public IAccountItem {
public:
    virtual Status getStatus();
    virtual QString getServerHostName();
    virtual QString getVirtualHub();
    virtual QString getNicName();
};

#endif // ABSTRACTNEWACCOUNT_H
