#include "modificarproductodialog.h"
#include "ui_modificarproductodialog.h"

ModificarProductoDialog::ModificarProductoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarProductoDialog)
{
    ui->setupUi(this);
}

ModificarProductoDialog::~ModificarProductoDialog()
{
    delete ui;
}

void ModificarProductoDialog::on_buttonBox_accepted()
{
    p2.setIdP(1);
    QString name = ui->lineEditNombreP->text();
    QString marca = ui->lineEditMarcaP->text();
    double precio =ui->lineEditPrecioP->text().toDouble();
    int cantidad = ui->lineEditCantidadP->text().toUInt();

    p2.setNombreP(name);
    p2.setMarcaP(marca);
    p2.setPrecioP(precio);
    p2.setCantidadP(cantidad);

    accept();
}

void ModificarProductoDialog::on_buttonBox_rejected()
{
    reject();
}
