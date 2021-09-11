#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QInputDialog>

#include "CmdAdapter.h"
#include "IVpnConnection.h"
#include "NewVpnConnection.h"
#include "VpnConnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef void (*DoubleClicked)(int, int);
=======
#include <QContextMenuEvent>

#include "Types.h"
#include "IAccountItem.h"
#include "AccountItem.h"
#include "NewAccountItem.h"
#include "ContextMenuNic.h"
#include "CmdAdapter.h"
#include "INicItem.h"
#include "NicItem.h"

using AccItems = QVector<IAccountItem*>;
using NicItems = QVector<INicItem*>;

namespace Ui {
class MainWindow;
}
>>>>>>> restart-project

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
<<<<<<< HEAD
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event) override;

private:
    void init();
    void initTableVpnConnection();
    void updateTableVpnConnection();
    void initTableVirtualAdapters();
    void updateTableVirtualAdapters();
    void initVpnConnectios();
    void freeVpnConnection();
    void createNic();
    void deleteNic(const QString& nicName);
    void disableNic(const QString& nicName);
    void enableNic(const QString& nicName);
    void connectTo(const QString& name);
    void disconnectTo(const QString& name);
    void deleteConnection(const QString& name);

private slots:
    void contextMenuVirtNetAdapters(const QPoint& pos);
    void contextMenuConSettings(const QPoint& pos);
    void newConWindow(int row, int column);
    void vpnConDoubleClicked(int row, int column);

private:
    Ui::MainWindow* _ui;
    QMap<unsigned, IVpnConnection*> _vpnCon;
};
=======
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
    void updateNicItems();
    AccItems getAccountItems();
    NicItems getNicItems();
    void freeAccItems();
    IAccountItem* getAccountItem(const QPoint& pos);
    INicItem* getNicItem(const QPoint& pos);
    IAccountItem* getAccountItem(int row, int column);
    INicItem* getNicItem(int row, int column);

private slots:
    void execCMenuVpnAcc(const QPoint&);
    void execCMenuNics(const QPoint&);
    void doubleClickVpnAcc(int row, int column);

private:
    Ui::MainWindow* _ui;
    AccItems _accItems;
    NicItems _nicItems;
    IAccountContextMenu* _cMenuVpnAcc; // Context menu for VPN Accounts
    INicContextMenu* _cMenuNics;   // Context menu for Network Interface Card
};

>>>>>>> restart-project
#endif // MAINWINDOW_H
