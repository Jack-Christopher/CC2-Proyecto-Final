#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <mutex>
#include <QSqlError>
#include <QSqlTableModel>
#include "controlproductosform.h"
#include "controlvendedoresform.h"

class DataBase
{
    static DataBase *dataBaseInstance;
    static std::mutex myMutex;
    static QSqlDatabase singletonDatabase;

    QString nombreDeConexion;

    DataBase(QString nombre);
    ~DataBase() {}

public:

    static DataBase *getInstance(QString nombreDeConexion);

    DataBase(DataBase &other) = delete;
    void operator=(const DataBase &) = delete;
    QSqlQuery doQuery(QString query);
    int doQuery(QString usuario, QString clave);
    void doQuery(QVector<std::tuple<QString,QString,QString>> &secuenciaDeUsuarios);
    static QSqlTableModel *newtablemodel(QSqlTableModel * modelo, ControlProductosForm * ptr);
    static QSqlTableModel *newtablemodel(QSqlTableModel * modelo, ControlVendedoresForm * ptr);
};

#endif // DATABASE_H
