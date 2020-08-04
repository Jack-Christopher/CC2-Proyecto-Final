#include "controlvendedoresform.h"
#include "ui_controlvendedoresform.h"
#include <QSqlTableModel>
#include <QSqlQuery>

ControlVendedoresForm::ControlVendedoresForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlVendedoresForm)
{
    ui->setupUi(this);
    configurarTabla();
}

ControlVendedoresForm::~ControlVendedoresForm()
{
    delete ui;
}

void ControlVendedoresForm::configurarTabla()
{

    modeloVendedor = new QSqlTableModel(this);
    modeloVendedor->setTable("vendedor");
    modeloVendedor->select();
    ui->tableViewVendedor->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewVendedor->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    modeloVendedor->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    modeloVendedor->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre"));
    modeloVendedor->setHeaderData(2, Qt::Horizontal, QObject::tr("Clave"));
    modeloVendedor->setHeaderData(3, Qt::Horizontal, QObject::tr("Privilegios"));
    ui->tableViewVendedor->setModel(modeloVendedor);
}

void ControlVendedoresForm::on_pushButtonEliminarU_clicked()
{
    QSqlQuery q;

    q.exec(QString("DELETE FROM vendedor WHERE id ==  '%1' ").arg(filaID));
    delete modeloVendedor;
    configurarTabla();
}

void ControlVendedoresForm::givePrivilegios(int fila)
{
    QSqlQuery q;

    q.exec(QString("UPDATE vendedor set isAdmin='%1'  WHERE id='%2'")
           .arg("Administrador")
           .arg(fila));

}

void ControlVendedoresForm::removePrivilegios(int fila)
{
    QSqlQuery q;

    q.exec(QString("UPDATE vendedor set isAdmin='%1'  WHERE id='%2'")
           .arg("No Administrador")
           .arg(fila));
}


void ControlVendedoresForm::on_pushButtonCambiarPrivilegios_clicked()
{
    QSqlQuery q;

    q.exec(QString("SELECT isAdmin FROM vendedor WHERE id='%1'")
           .arg(filaID));
    q.first();
    QString esAdmin;
    esAdmin = q.value(0).toString();

    void (*cambiar)(int);

    (esAdmin == "Administrador")?(cambiar = removePrivilegios):(cambiar = givePrivilegios);

    cambiar(filaID);

    delete modeloVendedor;
    configurarTabla();
}

void ControlVendedoresForm::on_tableViewVendedor_clicked(const QModelIndex &index)
{
    filaID = modeloVendedor->data(index).toInt();
}

int ControlVendedoresForm::getFilaID()
{
    return filaID;
}

