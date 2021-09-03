#ifndef CONTEXTMENUNIC_H
#define CONTEXTMENUNIC_H

#include "IContextMenu.h"
#include <QMenu>

class ContextMenuNic : public IContextMenu {
public:
    ContextMenuNic(QWidget* parent);
    ~ContextMenuNic() override;
    void exec(const QPoint &pos, const QString& rowName = "") override;

private:
    QMenu* _menu;
};

#endif // CONTEXTMENUNIC_H
