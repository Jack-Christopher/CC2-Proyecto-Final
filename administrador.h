#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <QString>

class Administrador
{
    int idAdmin;
    QString nombreAdmin;
    QString claveAdmin;
    QString privilegios;

public:
    Administrador(int id = -1, const QString &nombre = "", const QString &clave = "");

    int getId() const {return idAdmin;}
    QString getNombre() const {return nombreAdmin;}
    QString getClave() const {return claveAdmin;}
    QString getPrivilegios() const {return privilegios;}

    void setId(int newId) {idAdmin = newId;}
    void setNombre(QString &newNombre) {nombreAdmin= newNombre;}
    void setClave(QString &newClave) {claveAdmin = newClave;}

    void  operator= (Administrador newAdministrador);
};

#endif // ADMINISTRADOR_H
