#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H


#include "producto.h"
#include <QSqlQuery>
#include <thread>

class DataBaseFunctions
{
public:
    DataBaseFunctions();
    Producto operator()(int index);
    void operator()(Producto p1, int index);
    QString getThreadId(QString conexion, std::thread::id id);
};

#endif // DATABASEFUNCTIONS_H



