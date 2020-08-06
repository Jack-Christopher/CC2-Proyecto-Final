#include "facade.h"
#include "dialog.h"
#include "mainwindow.h"
#include "database.h"

namespace databaseInfo
{
    const QString DRIVER = "QSQLITE";
    const QString NOMBRE_BASE_DATOS  = "./data.db";
    const QString NOMBRE_CONEXION = "Conexion_";
}


Facade::Facade()
{

}


int Facade::ejecutarAplicacion(std::shared_ptr<QApplication> aplicacion)
{
    theState = esperando;

    while(theState != cerrarAplicacion)
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
        Facade::changeState( mainWindow.getStatus());
    }

    return  0;
}

int Facade::crea_configuraBaseDatos(QString usuario, QString clave)
{
    DataBase *db = DataBase::getInstance(databaseInfo::NOMBRE_CONEXION);
    int resultado = db->doQuery(usuario, clave);

    return resultado;

}


void Facade::ejecutarConfiguracion()
{
    Facade f;
    std::thread t1( &Facade::crea_configuraBaseDatos, f, "admin", "123");

    t1.join();
}


std::shared_ptr<QApplication> Facade::getSmartPointer(int argc, char *argv[])
{
    std::shared_ptr<QApplication> aplicacion;
    aplicacion = std::make_unique<QApplication> (argc, argv);

    return aplicacion;
}


void Facade::changeState(int st)
{
    if(st == 1)
    {
        theState = esperando;
    }
    else if (st == 1)
    {
        theState = cerrarSesion;
    }
    else if (st == 2)
    {
        theState = cerrarAplicacion;
    }
}
