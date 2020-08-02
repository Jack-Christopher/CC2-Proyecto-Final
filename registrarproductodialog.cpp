#include "registrarproductodialog.h"
#include "ui_registrarproductodialog.h"

#include <QMessageBox>

RegistrarProductoDialog::RegistrarProductoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrarProductoDialog)
{
    ui->setupUi(this);
}

RegistrarProductoDialog::~RegistrarProductoDialog()
{
    delete ui;
}

void RegistrarProductoDialog::on_buttonBox_accepted()
{
    p1.setIdP(1);
    QString name = ui->lineEditNombreP->text();
    QString marca = ui->lineEditMarcaP->text();
    double precio =ui->lineEditPrecioP->text().toDouble();
    int cantidad = ui->lineEditCantidadP->text().toInt();

    bool isNotOK = (name == "" || marca == "") || (precio <= 0 ||cantidad <= 0);


    if (isNotOK)
    {
        QMessageBox::warning(this, "Error", "Verifique bien los datos");
        return;
    }


    p1.setNombreP(name);
    p1.setMarcaP(marca);
    p1.setPrecioP(precio);
    p1.setCantidadP(cantidad);


    accept();
}

void RegistrarProductoDialog::on_buttonBox_rejected()
{
    reject();
}
