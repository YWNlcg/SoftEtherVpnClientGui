#ifndef CONTEXTMENUNIC_H
#define CONTEXTMENUNIC_H

#include <QMenu>

#include "INicItem.h"

class ContextMenuNic : public INicContextMenu {
public:
    ContextMenuNic(QWidget* parent);
    ~ContextMenuNic() override;
    void exec(const QPoint &pos, const INicItem* item) override;

private:
    QMenu* _menu;
};

#endif // CONTEXTMENUNIC_H
