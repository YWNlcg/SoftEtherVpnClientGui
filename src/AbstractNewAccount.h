#ifndef ABSTRACTNEWACCOUNT_H
#define ABSTRACTNEWACCOUNT_H

#include "IAccountItem.h"

class AbstractNewAccount : public IAccountItem {
public:
    virtual Status getStatus() const override;
    virtual QString getStatusStr() const override;
    virtual QString getServerHostName() const override;
    virtual QString getVirtualHub() const override;
    virtual QString getNicName() const override;
};

#endif // ABSTRACTNEWACCOUNT_H
