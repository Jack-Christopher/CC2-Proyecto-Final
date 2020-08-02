#include "producto.h"
#include <QString>

Producto::Producto(int id , const QString &nombre , const QString &marca, const double precio, const int cantidad)
    :idProducto(id)
    , nombreProducto(nombre)
    , marcaProducto(marca)
    , precioProducto(precio)
    , cantidadProducto(cantidad)


{

}

void Producto::operator-- (int n)
{
    cantidadProducto--;
}

void Producto::operator= (Producto newProducto)
{
    idProducto = newProducto.getIdP();
    nombreProducto = newProducto.getNombreP();
    marcaProducto = newProducto.getMarcaP();
    precioProducto = newProducto.getPrecio();
    cantidadProducto = newProducto.getCantidad();
}
