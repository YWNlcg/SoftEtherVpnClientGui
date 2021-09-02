#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include "Types.h"
#include "IContextMenu.h"

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

private slots:
    void execCMenuVpnAcc(const QPoint&);
    void execCMenuNics(const QPoint&);

private:
    Ui::MainWindow* _ui;
    IContextMenu* _cMenuVpnAcc; // Context menu for VPN Accounts
    IContextMenu* _cMenuNics;   // Context menu for Network Interface Card
};

#endif // MAINWINDOW_H
