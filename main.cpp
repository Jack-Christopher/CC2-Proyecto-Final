#include "facade.h"


int main(int argc, char *argv[])
{    
    Facade f;

    auto smartPointerToApp = f.getSmartPointer(argc, argv);

    f.ejecutarConfiguracion();

    auto resultado = f.ejecutarAplicacion(smartPointerToApp);

    return resultado;
}
