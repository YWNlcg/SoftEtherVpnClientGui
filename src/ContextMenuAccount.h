#ifndef CONTEXTMENUACCOUNT_H
#define CONTEXTMENUACCOUNT_H

#include <QMenu>
#include <QObject>

#include "IAccountItem.h"

#define QOBJ_NAME_ACTION_NEW "actionNew"
#define QOBJ_NAME_ACTION_STATUS "actionStatus"
#define QOBJ_NAME_ACTION_DELETE "actionDelete"
#define QOBJ_NAME_ACTION_CONNECT "actionConnect"
#define QOBJ_NAME_ACTION_DISCONNECT "actionDisconnect"


class ContextMenuAccount : public IAccountContextMenu {
public:
    ContextMenuAccount(QWidget* parent);
    // IContextMenu interface
    ~ContextMenuAccount() override;
    void exec(const QPoint& pos, IAccountItem* item) override;

private:
    void setDisableAll();

private slots:
    void newAccount();
    void deleteAccount();
    void statusAccount();
    void connectAccount();
    void disconnectAccount();

private:
    QMenu* _menu;
    QAction* _actionConnect;
    QAction* _actionStatus;
    QAction* _actionDisconnect;
    QAction* _actionNew;
    QAction* _actionDelete;
    IAccountItem* _item;
};

#endif // CONTEXTMENUACCOUNT_H
