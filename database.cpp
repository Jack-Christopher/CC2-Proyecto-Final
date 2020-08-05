#include "database.h"
#include <QString>
#include <QSqlQuery>
#include <thread>
#include <QDebug>
#include <QSqlError>
#include "databasefunctions.h"
#include "controlproductosform.h"
#include "controlvendedoresform.h"


DataBase::DataBase(QString nombreDeConexion)
{
    singletonDatabase = QSqlDatabase::addDatabase("QSQLITE", nombreDeConexion);
    if(singletonDatabase.databaseName() != "./data.db")
    {
        singletonDatabase.setDatabaseName("./data.db");
    }
}

DataBase *DataBase::dataBaseInstance{nullptr};
QSqlDatabase DataBase::singletonDatabase{};
std::mutex DataBase::myMutex;


DataBase *DataBase::getInstance(QString nombreDeConexion)
{
    if (dataBaseInstance == nullptr)
    {
        std::lock_guard<std::mutex> lock(myMutex);
        if (dataBaseInstance == nullptr)
        {
            dataBaseInstance = new DataBase(nombreDeConexion);
        }
    }

    return dataBaseInstance;
}

int DataBase::doQuery(QString usuario, QString clave)
{
    const QString DRIVER = "QSQLITE";

    //DataBase *db= DataBase::getInstance(nombreDeConexion);

    if (!QSqlDatabase::isDriverAvailable(DRIVER))
    {
        qDebug() << "Driver no existe";
        return -1;
    }
    else
    {

        if (!singletonDatabase.open())
        {
            qDebug() << singletonDatabase.lastError().text();
            return -2;
        }

        QSqlQuery q(singletonDatabase);
        q.exec("CREATE TABLE IF NOT EXISTS vendedor(id INTEGER PRIMARY KEY NOT NULL,"
               "nombre TEXT NOT NULL UNIQUE, clave TEXT NOT NULL, isAdmin TEXT NOT NULL)");

        q.exec(QString("INSERT INTO vendedor (id, nombre, clave,isAdmin) VALUES (1,'%1', '%2', 'Administrador')")
               .arg(usuario)
               .arg(clave));

        q.exec("CREATE TABLE IF NOT EXISTS producto(id INTEGER PRIMARY KEY NOT NULL,"
               "nombre TEXT NOT NULL, marca TEXT NOT NULL , precio DOUBLE NOT NULL, cantidad INT NOT NULL)");
    }

    return 0;
}


void DataBase::doQuery(QVector<std::tuple<QString,QString,QString>> &secuenciaDeUsuarios)
{
    QSqlQuery q(singletonDatabase);

    singletonDatabase.open();

    q.exec("SELECT nombre, clave, isAdmin FROM vendedor");

    while (q.next())
    {
        QString nombre = q.value(0).toString();
        QString clave = q.value(1).toString();
        QString isAdmin = q.value(2).toString();
        std::tuple<QString,QString,QString> Usuario(nombre, clave, isAdmin);

        secuenciaDeUsuarios.append(Usuario);
    }

    std::tuple<QString,QString,QString> Usuario("admin", "123", "Administrador");

    secuenciaDeUsuarios.append(Usuario);
}

QSqlQuery DataBase::doQuery(QString query)
{
    QSqlQuery q(singletonDatabase);
    q.exec(query);
    return q;
}


QSqlTableModel *DataBase::newtablemodel(QSqlTableModel * modelo, ControlProductosForm * ptr)
{
    modelo = new QSqlTableModel(ptr, singletonDatabase);
    modelo->setTable("producto");
    modelo->select();
    modelo->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modelo->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
    modelo->setHeaderData(2, Qt::Horizontal, QObject::tr("Marca"));
    modelo->setHeaderData(3, Qt::Horizontal, QObject::tr("Precio"));
    modelo->setHeaderData(4, Qt::Horizontal, QObject::tr("Cantidad"));

    return modelo;
}


QSqlTableModel *DataBase::newtablemodel(QSqlTableModel * modelo, ControlVendedoresForm * ptr)
{
    modelo = new QSqlTableModel(ptr, singletonDatabase);
    modelo->setTable("vendedor");
    modelo->select();
    modelo->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modelo->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
    modelo->setHeaderData(2, Qt::Horizontal, QObject::tr("Clave"));
    modelo->setHeaderData(3, Qt::Horizontal, QObject::tr("Privilegios"));
    return modelo;
}

