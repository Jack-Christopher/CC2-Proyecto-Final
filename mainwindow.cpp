#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controlvendedoresform.h"
#include "controlproductosform.h"
#include "registrarproductodialog.h"
#include "registrarvendedordialog.h"
#include "modificarproductodialog.h"
#include "dialog.h"
#include "administrador.h"
#include "vendedor.h"
#include "databasefunctions.h"
#include "database.h"

#include <QMessageBox>
#include <QMdiSubWindow>
#include <QSqlQuery>
#include <QDebug>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    status= 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox::information(this, "Mensaje", "Este programa fue desarrollado por el equipo DELTA");
}

void MainWindow::on_actionMostrar_Productos_triggered()
{
    ctrlP = new ControlProductosForm(this);
    qmdsw = ui->mdiArea->addSubWindow(ctrlP);
    qmdsw->setGeometry(ctrlP->geometry());
    qmdsw->setWindowTitle(ctrlP->windowTitle());
    qmdsw->show();
}

void MainWindow::on_actionRegistrar_Productos_triggered()
{
    RegistrarProductoDialog p(this);
    if (p.exec() == QDialog::Rejected)
    {
        return;
    }
    auto prod = p.getProducto();

    DataBaseFunctions dbf;
    QString nombreDeConexion =  dbf.getThreadId("Conexion_", std::this_thread::get_id());

    DataBase *db = DataBase::getInstance(nombreDeConexion);

    QString query = QString("INSERT INTO producto (nombre, marca, precio, cantidad) VALUES ('%1', '%2', '%3', '%4')")
            .arg(prod.getNombreP())
            .arg(prod.getMarcaP())
            .arg(prod.getPrecio())
            .arg(prod.getCantidad()) ;

    db->doQuery(query);


    delete ctrlP;
    ui->mdiArea->closeAllSubWindows();

    on_actionMostrar_Productos_triggered();
}

template<typename Tipo>
void MainWindow::insertarUsuario(Tipo *usuario)
{
    DataBaseFunctions dbf;
    QString nombreDeConexion =  dbf.getThreadId("Conexion_", std::this_thread::get_id());

    DataBase *db = DataBase::getInstance(nombreDeConexion);

    QString query = QString("INSERT INTO vendedor (nombre, clave, isAdmin) VALUES ('%1', '%2', '%3')")
            .arg(usuario->getNombre())
            .arg(usuario->getClave())
            .arg(usuario->getPrivilegios());
    db->doQuery(query);

    delete usuario;
}



void MainWindow::on_actionRegistrar_Usuarios_triggered()
{
    RegistrarVendedorDialog d(this);
    if (d.exec() == QDialog::Rejected)
    {
        return;
    }

    auto *vend = new Vendedor(d.getVendedor());
    auto *admi = new Administrador( d.getAdministrador());

    if(vend->getNombre() == "")
    {
        insertarUsuario<Administrador>(admi);
        delete vend;
    }
    else
    {
        insertarUsuario<Vendedor>(vend);
        delete admi;
    }

    ui->mdiArea->closeAllSubWindows();
    on_actionMostrar_Usuarios_triggered();
}

void MainWindow::on_actionMostrar_Usuarios_triggered()
{
    ctrlV = new ControlVendedoresForm(this);
    qmdsw = ui->mdiArea->addSubWindow(ctrlV);
    qmdsw->setGeometry(ctrlV->geometry());
    qmdsw->setWindowTitle(ctrlV->windowTitle());
    qmdsw->show();
}

void MainWindow::setPrivilegios(bool isAdministrador)
{
    if (!isAdministrador)
    {
        ui->actionMostrar_Usuarios->setEnabled(false);
        ui->actionRegistrar_Usuarios->setEnabled(false);
        ui->actionRegistrar_Productos->setEnabled(false);
        ui->actionModificar_Producto->setEnabled(false);
    }
}

int MainWindow::getStatus()
{
    return  status;
}

void MainWindow::on_actionCerrarSesion_triggered()
{
    status = 1;
    close();
}

void MainWindow::on_actionSalir_triggered()
{
    status = 2;
    close();
}

void MainWindow::on_actionModificar_Producto_triggered()
{
    ModificarProductoDialog mp(this);
    if (mp.exec() == QDialog::Rejected)
    {
        return;
    }
    auto prod = mp.getProducto();


    DataBaseFunctions dbf;
    QString nombreDeConexion =  dbf.getThreadId("Conexion_", std::this_thread::get_id());

    DataBase *db = DataBase::getInstance(nombreDeConexion);

    QString query = QString("UPDATE producto set nombre='%1', marca='%2' , precio='%3',"
                   " cantidad='%4'  WHERE id='%5'")
           .arg(prod.getNombreP())
           .arg(prod.getMarcaP())
           .arg(prod.getPrecio())
           .arg(prod.getCantidad())
           .arg(ctrlP->getFilaID());

    db->doQuery(query);

    delete ctrlP;
    ctrlP = new ControlProductosForm(this);
    ui->mdiArea->closeAllSubWindows();
    on_actionMostrar_Productos_triggered();
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    if (status == 1)
    {
        event->accept();
        return;
    }
    auto resBtn = QMessageBox::question(
                this, "Salir", tr("¿Estás seguro?"),
                QMessageBox::No | QMessageBox::Yes,  QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        status = 2;
    }
}


