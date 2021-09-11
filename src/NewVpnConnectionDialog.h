#ifndef NEWVPNCONNECTIONDIALOG_H
#define NEWVPNCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class NewVpnConnectionDialog;
}

class NewVpnConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewVpnConnectionDialog(QWidget *parent = nullptr);
    ~NewVpnConnectionDialog();

private:
    Ui::NewVpnConnectionDialog *ui;
};

#endif // NEWVPNCONNECTIONDIALOG_H
