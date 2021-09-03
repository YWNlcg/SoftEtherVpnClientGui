#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include "Types.h"
#include "IContextMenu.h"
#include "IAccountItem.h"
#include "AccountItem.h"
#include "NewAccountItem.h"
#include "CmdAdapter.h"


using AccItems = QVector<IAccountItem*>;
CmdAdapter& GetCmdAdapterInstance();

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCMenuVpnAcc(IContextMenu* cMenu);
    void setCMenuNics(IContextMenu* cMenu);

private:
    void initPolicy();
    void initAccItems();
    void updateAccItems();
    AccItems getAccountItems();
    void freeAccItems();

private slots:
    void execCMenuVpnAcc(const QPoint&);
    void execCMenuNics(const QPoint&);

private:
    Ui::MainWindow* _ui;
    AccItems _accItems;
    IContextMenu* _cMenuVpnAcc; // Context menu for VPN Accounts
    IContextMenu* _cMenuNics;   // Context menu for Network Interface Card
};

#endif // MAINWINDOW_H
