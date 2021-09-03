#ifndef ABSTRACTNEWACCOUNT_H
#define ABSTRACTNEWACCOUNT_H

#include "IAccountItem.h"

class AbstractNewAccount : public IAccountItem {
public:
    virtual Status getStatus() override;
    virtual QString getStatusStr() override;
    virtual QString getServerHostName() override;
    virtual QString getVirtualHub() override;
    virtual QString getNicName() override;
};

#endif // ABSTRACTNEWACCOUNT_H
