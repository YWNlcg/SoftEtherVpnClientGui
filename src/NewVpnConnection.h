#ifndef NEWVPNCONNECTION_H
#define NEWVPNCONNECTION_H

#include <QMainWindow>
#include <QCloseEvent>
#include "IVpnConnection.h"
#include "CmdAdapter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class newVpnConSettingWindow; }
QT_END_NAMESPACE

using AuthType = AccountAdapter::AuthType;

class NewVpnConnection : public IVpnConnection, public QMainWindow {
public:
    NewVpnConnection(QString name, QWidget* parent = nullptr);
    ~NewVpnConnection();
    QString getName() override;
    Status getStatus() override;
    QString getVpnServerName() override;
    QString getVirtualHub() override;
    QString getVirtualNetworkAdapter() override;
    void openWindow() override;

private:
    void initWindow();
    void updateListNics();
    void setAnonAuth();
    void setStandartAuth();
    void setRadiusAuth();
    void setCertificateAuth();
    void setSmartCardAuth();
    void clearAuthType();
    AuthType getAuthType();
    void dataCkecking();

private slots:
    void createNewConnection();
    void updateAuthMethod(int index);
    void checkLineEdit(const QString& text);
    void checkListWidget(int currentRow);

private:
    Ui::newVpnConSettingWindow* _ui;
    QString _name;
};

#endif // NEWVPNCONNECTION_H
