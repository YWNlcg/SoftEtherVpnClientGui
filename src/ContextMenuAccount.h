#ifndef CONTEXTMENUACCOUNT_H
#define CONTEXTMENUACCOUNT_H

#include "IContextMenu.h"
#include <QMenu>

class ContextMenuAccount : public IContextMenu {
public:
    ContextMenuAccount(QWidget* parent);
    ~ContextMenuAccount() override;
    void exec(const QPoint &pos, const QString& rowName = "") override;

private:
    QMenu* _menu;
};

#endif // CONTEXTMENUACCOUNT_H
