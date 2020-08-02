#include "registrarvendedordialog.h"
#include "ui_registrarvendedordialog.h"

#include <QString>
#include <QMessageBox>

RegistrarVendedorDialog::RegistrarVendedorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrarVendedorDialog),
    v1(-1, "", "")
{
    ui->setupUi(this);
    ui->claveLineEdit->setEchoMode(QLineEdit::Password);
    ui->repiteClaveLineEdit->setEchoMode(QLineEdit::Password);
}

RegistrarVendedorDialog::~RegistrarVendedorDialog()
{
    delete ui;
}

void RegistrarVendedorDialog::on_buttonBoxRegistrar_accepted()
{
    bool isAdministrador = ui->checkBoxIsAdmin->checkState();

    if (isAdministrador)
    {
        admin.setId(1);
        QString name = ui->usuarioLineEdit->text();
        QString password = ui->claveLineEdit->text();

        admin.setNombre(name);
        admin.setClave(password);
        if(admin.getClave() != ui->repiteClaveLineEdit->text())
        {
            QMessageBox::critical(this, "Error", "Las contraseñas deben ser iguales");
            return;
        }
    }
    else
    {
        v1.setId(1);
        QString name = ui->usuarioLineEdit->text();
        QString password = ui->claveLineEdit->text();

        v1.setNombre(name);
        v1.setClave(password);
        if(v1.getClave() != ui->repiteClaveLineEdit->text())
        {
            QMessageBox::critical(this, "Error", "Las contraseñas deben ser iguales");
            return;
        }
    }

    accept();
}

void RegistrarVendedorDialog::on_buttonBoxRegistrar_rejected()
{
    reject();
}
