#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>

#include "CmdAdapter.h"
#include "IVpnConnection.h"
#include "NewVpnConnection.h"
#include "VpnConnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef void (*DoubleClicked)(int, int);

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
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
#endif // MAINWINDOW_H
