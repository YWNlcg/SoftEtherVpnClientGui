#ifndef NEWVPNCONNECTIONDIALOG_H
#define NEWVPNCONNECTIONDIALOG_H

#include <QDialog>
#include <QListWidget>

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
    void createAccount();
    void dataValidation();

private slots:
    void onButtonBoxClicked(QAbstractButton *button);

private:
    Ui::NewVpnConnectionDialog *_ui;
};

#endif // NEWVPNCONNECTIONDIALOG_H
