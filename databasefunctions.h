#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H


#include "producto.h"
#include <QSqlQuery>

class DataBaseFunctions
{
public:
    DataBaseFunctions();
    Producto operator()(int index);
    void operator()(Producto p1, int index);
};

#endif // DATABASEFUNCTIONS_H



