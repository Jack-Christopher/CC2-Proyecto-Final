#include "facade.h"


int main(int argc, char *argv[])
{    
    Facade f;

    f.ejecutarConfiguracion();

    auto smartPointerToApp = f.getSmartPointer(argc, argv);

    auto resultado = f.ejecutarAplicacion(smartPointerToApp);

    return resultado;
}
