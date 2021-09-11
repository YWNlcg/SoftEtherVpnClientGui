#ifndef INICITEM_H
#define INICITEM_H

#include <QObject>

class INicItem {
public:

};

class INicContextMenu : public QObject {
    Q_OBJECT
public:
    virtual ~INicContextMenu() {};
    virtual void exec(const QPoint& pos, const INicItem* item) = 0;
};

#endif // INICITEM_H
