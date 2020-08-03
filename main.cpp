#include "dialog.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


namespace databaseInfo
{
    const static QString DRIVER = "QSQLITE";
    const static QString NOMBRE_BASE_DATOS  = "./data.db";
}


int creaBaseDatos()
{
    if (!QSqlDatabase::isDriverAvailable(databaseInfo::DRIVER))
    {
        qDebug() << "Driver no existe";
        return -1;
    }
    else
    {
        auto db = QSqlDatabase::addDatabase(databaseInfo::DRIVER);
        db.setDatabaseName(databaseInfo::NOMBRE_BASE_DATOS);
        if (!db.open())
        {
            qDebug() << db.lastError().text();
            return -2;
        }
    }
    return 0;
}


void configuraBaseDatos()
{
    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS vendedor(id INTEGER PRIMARY KEY NOT NULL,"
           "nombre TEXT NOT NULL UNIQUE, clave TEXT NOT NULL, isAdmin TEXT NOT NULL)");

    q.exec("INSERT INTO vendedor (id, nombre, clave,isAdmin) VALUES (1,'admin', '123456', 'Administrador')");

    q.exec("CREATE TABLE IF NOT EXISTS producto(id INTEGER PRIMARY KEY NOT NULL,"
           "nombre TEXT NOT NULL, marca TEXT NOT NULL , precio DOUBLE NOT NULL, cantidad INT NOT NULL)");
}


void main(int argc, char *argv[])
{
    int Salir = 0;

    const int resultado = creaBaseDatos();
    if (resultado < 0)
    {
        return ;
    }
    configuraBaseDatos();

    std::unique_ptr<QApplication> aplicacion;
    aplicacion = std::make_unique<QApplication> (argc, argv);

    while(Salir != 2)
    {
        aplicacion->setStyle("fusion");

        Dialog login;

        if (login.exec() == QDialog::Rejected)
        {
            return ;
        }

        MainWindow mainWindow;
        mainWindow.setPrivilegios(login.getIsAdmin());
        mainWindow.show();

        aplicacion->exec();
        Salir = mainWindow.getStatus();
    }
}
