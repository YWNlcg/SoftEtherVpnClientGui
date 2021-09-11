#ifndef NEWVPNCONNECTIONDIALOG_H
#define NEWVPNCONNECTIONDIALOG_H

#include <QDialog>

#include "Extern.h"

namespace Ui {
class NewVpnConnectionDialog;
}

class NewVpnConnectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewVpnConnectionDialog(QWidget *parent = nullptr);
    ~NewVpnConnectionDialog();
    void setAccountData(const RpcGetAccount* ac);

private:
    void init();
    bool checkSettingName(const QString& name);

private:
    Ui::NewVpnConnectionDialog *_ui;
};

#endif // NEWVPNCONNECTIONDIALOG_H
