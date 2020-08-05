#include "dialog.h"
#include "mainwindow.h"
#include "database.h"
#include "databasefunctions.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <thread>
#include <QDebug>
#include <sstream>


namespace databaseInfo
{
    const QString DRIVER = "QSQLITE";
    const QString NOMBRE_BASE_DATOS  = "./data.db";
    const QString NOMBRE_CONEXION = "Conexion_";
}


int crea_configuraBaseDatos(QString usuario, QString clave)
{

    DataBase *db = DataBase::getInstance(databaseInfo::NOMBRE_CONEXION);

    int resultado = db->doQuery(usuario, clave);

    return resultado;

}


int main(int argc, char *argv[])
{
    int Salir = 0;

    std::unique_ptr<QApplication> aplicacion;
    aplicacion = std::make_unique<QApplication> (argc, argv);

    std::thread t1(crea_configuraBaseDatos, "admin", "123");

    t1.join();


    while(Salir != 2)
    {
        aplicacion->setStyle("fusion");

        Dialog login;

        if (login.exec() == QDialog::Rejected)
        {
            return -1;
        }

        MainWindow mainWindow;
        mainWindow.setPrivilegios(login.getIsAdmin());
        mainWindow.show();

        aplicacion->exec();
        Salir = mainWindow.getStatus();
    }
    return 0;
}
