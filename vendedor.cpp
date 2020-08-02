#include "vendedor.h"

Vendedor::Vendedor(int id , const QString &nombre , const QString &clave)
    :idVendedor(id)
    , nombreVendedor(nombre)
    , claveVendedor(clave)
    , privilegios("No Administrador")
{


}


bool operator<( Vendedor newVendedor, Vendedor oldVendedor)
{
    bool isLess;

    int x = oldVendedor.getNombre().compare(newVendedor.getNombre());
    (x < 0)?(isLess = false):(isLess = true);
    return isLess;
}


void  Vendedor::operator= (Vendedor newVendedor)
{
    idVendedor = newVendedor.getId();
    nombreVendedor = newVendedor.getNombre();
    claveVendedor = newVendedor.getClave();
    privilegios = newVendedor.getPrivilegios();
}
