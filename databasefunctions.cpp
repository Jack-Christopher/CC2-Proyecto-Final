#include "databasefunctions.h"
#include <QSqlQuery>
#include <QString>
#include <QVariant>
#include "producto.h"

DataBaseFunctions::DataBaseFunctions()
{

}


Producto DataBaseFunctions::operator()(int index)
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


void DataBaseFunctions::operator()(Producto p1, int index)
{
    QSqlQuery q;
    q.exec(QString("UPDATE producto SET nombre = '%1', marca = '%2', precio = '%3', cantidad = '%4' WHERE id = '%5'")
           .arg(p1.getNombreP())
           .arg(p1.getMarcaP())
           .arg(p1.getPrecio())
           .arg(p1.getCantidad())
           .arg(index));
}

