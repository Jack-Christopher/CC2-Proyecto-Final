#include "controlproductosform.h"
#include "ui_controlproductosform.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

ControlProductosForm::ControlProductosForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlProductosForm)
{
    ui->setupUi(this);
    configurarTabla();
}

ControlProductosForm::~ControlProductosForm()
{
    delete ui;
}

void ControlProductosForm::configurarTabla()
{

    modeloProducto = new QSqlTableModel(this);
    modeloProducto->setTable("producto");
    modeloProducto->select();
    ui->tableViewProductos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewProductos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    modeloProducto->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modeloProducto->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
    modeloProducto->setHeaderData(2, Qt::Horizontal, QObject::tr("Marca"));
    modeloProducto->setHeaderData(3, Qt::Horizontal, QObject::tr("Cantidad"));
    ui->tableViewProductos->setModel(modeloProducto);
}

Producto ControlProductosForm::fromDBToObject(int index)
{
    QSqlQuery q;
    q.exec(QString( "SELECT nombre, marca, precio, cantidad FROM producto WHERE id == '%1' ").arg(index));
    q.next();

    QString nombre = q.value(0).toString();
    QString marca = q.value(1).toString();
    double precio = q.value(2).toString().toDouble();
    int cantidad= q.value(3).toString().toInt();

    Producto p1;
    p1.setMarcaP(marca);
    p1.setNombreP(nombre);
    p1.setPrecioP(precio);
    p1.setCantidadP(cantidad);

    return p1;
}

void ControlProductosForm::fromObjectToDB(Producto &p1)
{
    QSqlQuery q;
    q.exec(QString("UPDATE producto SET nombre = '%1', marca = '%2', precio = '%3', cantidad = '%4' WHERE id = '%5'")
           .arg(p1.getNombreP())
           .arg(p1.getMarcaP())
           .arg(p1.getPrecio())
           .arg(p1.getCantidad())
           .arg(filaID));
}



void ControlProductosForm::on_pushButtonEliminarP_clicked()
{
    QSqlQuery q;

    q.exec(QString("DELETE FROM producto WHERE id ==  '%1' ").arg(filaID));
    delete modeloProducto;
    configurarTabla();

}

void ControlProductosForm::on_pushButtonVenderP_clicked()
{

    Producto p = fromDBToObject(filaID);
    p--;
    if(p.getCantidad() > 0)
    {
        fromObjectToDB(p);

        delete modeloProducto;
        configurarTabla();
    }
    else
    {
        on_pushButtonEliminarP_clicked();
    }
}


void ControlProductosForm::on_tableViewProductos_clicked(const QModelIndex &index)
{
    filaID = modeloProducto->data(index).toInt();
}

int ControlProductosForm::getFilaID()
{
    return filaID;
}




