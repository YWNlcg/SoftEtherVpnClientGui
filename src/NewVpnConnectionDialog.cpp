#include "NewVpnConnectionDialog.h"
#include "ui_NewVpnConnectionDialog.h"

NewVpnConnectionDialog::NewVpnConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewVpnConnectionDialog) {
    ui->setupUi(this);
}

NewVpnConnectionDialog::~NewVpnConnectionDialog() {
    delete ui;
}
