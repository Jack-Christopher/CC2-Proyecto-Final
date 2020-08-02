#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "administrador.h"

#include <QString>
#include <QDebug>

class Vendedor : public Administrador
{
    int idVendedor;
    QString nombreVendedor;
    QString claveVendedor;
    QString privilegios;

public:
    Vendedor(int id = -1, const QString &nombre = "", const QString &clave = "");

    int getId() const {return idVendedor;}
    QString getNombre() const {return nombreVendedor;};
    QString getClave() const {return claveVendedor;};
    QString getPrivilegios() const {return privilegios;}

    void setId(int newId) {idVendedor = newId;}
    void setNombre(QString &newNombre) {nombreVendedor= newNombre;}
    void setClave(QString &newClave) {claveVendedor = newClave;}
    void setPrivilegios(QString &newstatus) {privilegios = newstatus;}

    void  operator= (Vendedor newVendedor);

    friend bool operator<( Vendedor newVendedor, Vendedor oldVendedor);

};

#endif // VENDEDOR_H



