#ifndef NICITEM_H
#define NICITEM_H

#include "INicItem.h"

class NicItem : public INicItem {
public:
    NicItem();
    QString getTitle() const;
    NicStatus getStatus() const;
    QString getMacAddr() const;
    QString getVersion() const;
};

#endif // NICITEM_H
