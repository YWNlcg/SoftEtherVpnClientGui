#ifndef ICONTEXTMENU_H
#define ICONTEXTMENU_H

#include <QObject>

class IContextMenu {
public:
    virtual ~IContextMenu() {};
    virtual void exec(const QPoint& pos) = 0;
};

#endif // ICONTEXTMENU_H
