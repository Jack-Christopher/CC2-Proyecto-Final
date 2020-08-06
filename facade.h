#ifndef FACADE_H
#define FACADE_H


#include <thread>
#include <QApplication>

enum state { esperando, cerrarSesion, cerrarAplicacion};

class Facade
{    
    state theState;
public:
    Facade();

    int ejecutarAplicacion(std::shared_ptr<QApplication> aplicacion);

    void ejecutarConfiguracion();

    int crea_configuraBaseDatos(QString usuario, QString clave);

    std::shared_ptr<QApplication> getSmartPointer(int argc, char *argv[]);

    void changeState(int st);



};

#endif // FACADE_H
