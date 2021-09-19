#ifndef NEWVPNCONNECTIONDIALOG_H
#define NEWVPNCONNECTIONDIALOG_H

#include <QDialog>
#include <QListWidget>

#include "Extern.h"
#include "Types.h"
#include "LogHandler.h"

#define QOBJECT_NAME_PASSWORD "lineEditPassword"

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
    int createAccount();
    void dataValidation();
    AuthType getAuthType();
    void removeAuth();
    void setAnonimousAuth();
    void setStandartAuth();
    void setRadiusAuth();
    void setCertAuth();
    void setSmartCardAuth();

private slots:
    void onButtonBoxClicked(QAbstractButton *button);
    void onAuthTypeChanged(int index);

private:
    Ui::NewVpnConnectionDialog *_ui;
};

#endif // NEWVPNCONNECTIONDIALOG_H
