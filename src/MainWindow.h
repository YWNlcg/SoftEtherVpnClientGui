#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>

#include "Types.h"
#include "IAccountItem.h"
#include "AccountItem.h"
#include "NewAccountItem.h"
#include "ContextMenuNic.h"
#include "CmdAdapter.h"


using AccItems = QVector<IAccountItem*>;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCMenuVpnAcc(IAccountContextMenu* cMenu);
    void setCMenuNics(INicContextMenu* cMenu);

private:
    void initPolicy();
    void initAccItems();
    void initAccTable();
    void initNicTable();
    void updateAccTable();
    void updateNicTable();
    void updateAccItems();
    AccItems getAccountItems();
    void freeAccItems();

private slots:
    void execCMenuVpnAcc(const QPoint&);
    void execCMenuNics(const QPoint&);

private:
    Ui::MainWindow* _ui;
    AccItems _accItems;
    IAccountContextMenu* _cMenuVpnAcc; // Context menu for VPN Accounts
    INicContextMenu* _cMenuNics;   // Context menu for Network Interface Card
};

#endif // MAINWINDOW_H
