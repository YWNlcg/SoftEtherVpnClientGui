#ifndef CONTEXTMENUNIC_H
#define CONTEXTMENUNIC_H

#include "IContextMenu.h"
#include <QMenu>

class ContextMenuNic : public IContextMenu {
public:
    ContextMenuNic(QWidget* parent);
    ~ContextMenuNic() override;
    void exec(const QPoint &pos) override;

private:
    QMenu* _menu;
};

#endif // CONTEXTMENUNIC_H
