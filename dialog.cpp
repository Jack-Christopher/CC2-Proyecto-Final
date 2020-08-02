#include "dialog.h"
#include "ui_dialog.h"
#include "registrarvendedordialog.h"
#include "registrarproductodialog.h"
#include "mainwindow.h"
#include "vendedor.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QtAlgorithms>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->claveLineEdit->setEchoMode(QLineEdit::Password);

    QSqlQuery q;

    q.exec("SELECT nombre, clave, isAdmin FROM vendedor");

    while (q.next())
    {
        QString nombre = q.value(0).toString();
        QString clave = q.value(1).toString();
        QString isAdmin = q.value(2).toString();
        std::tuple<QString,QString,QString> Usuario(nombre, clave, isAdmin);

        secuenciaDeUsuarios.append(Usuario);
    }

    int i, j, min_idx;

    for (i = 0; i < secuenciaDeUsuarios.size()-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < secuenciaDeUsuarios.size(); j++)
            if (secuenciaDeUsuarios[j] < secuenciaDeUsuarios[min_idx])
                min_idx = j;

        std::tuple<QString,QString,QString>  temp = secuenciaDeUsuarios[min_idx];
        secuenciaDeUsuarios[min_idx] = secuenciaDeUsuarios[i];
        secuenciaDeUsuarios[i] = temp;
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBoxLogin_accepted()
{

    QSqlQuery q;

    bool isAdministrador = ui->checkBoxIsAdmin->checkState();

    QString nombre = ui->usuarioLineEdit->text();
    QString clave =  ui->claveLineEdit->text();
    QString privilegios = (isAdministrador)?("Administrador"):("No Administrador");

    std::tuple<QString,QString,QString> usuario = std::make_tuple (nombre, clave, privilegios);

    bool  LoginOK = std::binary_search( std::begin(secuenciaDeUsuarios), std::end(secuenciaDeUsuarios), usuario);

    if (LoginOK)
    {
        (privilegios == "Administrador")?(isAdmin = true):(isAdmin = false);
    }
    else
    {
        QMessageBox::warning(this, "Aviso", "El nombre de usuario o la contraseña son incorrectos" );
        return;
    }


    accept();
}

void Dialog::on_buttonBoxLogin_rejected()
{
    reject();
}

bool Dialog::getIsAdmin()
{
    return isAdmin;
}

