#ifndef INICITEM_H
#define INICITEM_H

#include <QObject>

#include "Types.h"

class INicItem {
public:
    virtual ~INicItem() {};
    virtual QString getTitle() const = 0;
    virtual NicStatus getStatus() const = 0;
    virtual QString getStatusStr() const = 0;
    virtual QString getMacAddr() const = 0;
    virtual QString getVersion() const = 0;
};

class INicContextMenu : public QObject {
    Q_OBJECT
public:
    virtual ~INicContextMenu() {};
    virtual void exec(const QPoint& pos, INicItem* item) = 0;
};

#endif // INICITEM_H
