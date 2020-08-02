#include "administrador.h"

Administrador::Administrador(int id , const QString &nombre , const QString &clave)
    :idAdmin(id)
    , nombreAdmin(nombre)
    , claveAdmin(clave)
    , privilegios("Administrador")
{

}


void  Administrador::operator= (Administrador newAdministrador)
{
    idAdmin = newAdministrador.getId();
    nombreAdmin = newAdministrador.getNombre();
    claveAdmin = newAdministrador.getClave();
    privilegios = newAdministrador.getPrivilegios();
}
