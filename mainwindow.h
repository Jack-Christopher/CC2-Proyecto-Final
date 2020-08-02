#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QVector>
#include "administrador.h"
#include "vendedor.h"
#include "dialog.h"
#include "controlproductosform.h"
#include "controlvendedoresform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setPrivilegios(bool isAdministrador);
    static void insertarAdmin(Administrador *adm, Vendedor *ven);
    static void insertarVendedor(Administrador *adm, Vendedor *ven);
    int getStatus();
    void closeEvent (QCloseEvent *event);
    ~MainWindow();

private slots:

    void on_actionAcerca_de_triggered();

    void on_actionMostrar_Productos_triggered();

    void on_actionRegistrar_Productos_triggered();

    void on_actionRegistrar_Usuarios_triggered();

    void on_actionMostrar_Usuarios_triggered();

    void on_actionCerrarSesion_triggered();

    void on_actionSalir_triggered();

    void on_actionModificar_Producto_triggered();

private:
    Ui::MainWindow *ui;

    int status;

    Administrador ad1;
    Vendedor d1;

    ControlProductosForm *ctrlP;
    ControlVendedoresForm *ctrlV;

    QMdiSubWindow *qmdsw;
};

#endif // MAINWINDOW_H
