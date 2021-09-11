#ifndef CONTEXTMENUNIC_H
#define CONTEXTMENUNIC_H

#include <QMenu>

#include "INicItem.h"

class ContextMenuNic : public INicContextMenu {
public:
    ContextMenuNic(QWidget* parent);
    ~ContextMenuNic() override;
    void exec(const QPoint &pos, INicItem* item) override;

private:
    void setDisableAll();

private:
    QMenu* _menu;
    QAction* _actionNewVNA;
    QAction* _actionEnable;
    QAction* _actionDisable;
    QAction* _actionDelete;
    INicItem* _item;
};

#endif // CONTEXTMENUNIC_H
