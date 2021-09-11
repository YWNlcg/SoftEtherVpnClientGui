#ifndef IACCOUNTITEM_H
#define IACCOUNTITEM_H

#include <QObject>
#include <QString>

#include "Types.h"

class IAccountItem {
public:
    virtual ~IAccountItem() {};
    virtual QString getTitle() const = 0;
    virtual AccStatus getStatus() const = 0;
    virtual QString getStatusStr() const = 0;
    virtual QString getServerHostName() const = 0;
    virtual QString getVirtualHub() const = 0;
    virtual QString getNicName() const = 0;
    virtual void doubleClick(QObject* parent = NULL) = 0;
};

class IAccountContextMenu : public QObject {
    Q_OBJECT
public:
    virtual ~IAccountContextMenu() {};
    virtual void exec(const QPoint& pos, IAccountItem* item) = 0;
};

#endif // IACCOUNTITEM_H
