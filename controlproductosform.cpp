#include "controlproductosform.h"
#include "ui_controlproductosform.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDebug>

#include "databasefunctions.h"

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


void ControlProductosForm::on_pushButtonEliminarP_clicked()
{
    QSqlQuery q;

    q.exec(QString("DELETE FROM producto WHERE id ==  '%1' ").arg(filaID));
    delete modeloProducto;
    configurarTabla();

}

void ControlProductosForm::on_pushButtonVenderP_clicked()
{
    DataBaseFunctions dbf;

    Producto p = dbf(filaID);
    p--;
    if(p.getCantidad() > 0)
    {
        dbf(p, filaID);

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




