#ifndef NICITEM_H
#define NICITEM_H

#include "Types.h"
#include "INicItem.h"


class NicItem : public INicItem {
public:
    NicItem(const Nic& nic);
    QString getTitle() const;
    NicStatus getStatus() const;
    QString getStatusStr() const;
    QString getMacAddr() const;
    QString getVersion() const;

private:
    Nic _nic;
};

#endif // NICITEM_H
