#ifndef CONTROLPRODUCTOSFORM_H
#define CONTROLPRODUCTOSFORM_H

#include <QWidget>
#include <QMdiSubWindow>

#include "producto.h"

namespace Ui {
class ControlProductosForm;
}

class QSqlTableModel;

class ControlProductosForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlProductosForm(QWidget *parent = nullptr);
    int getFilaID();
    void configurarTabla();
    Producto fromDBToObject(int index);
    void fromObjectToDB (Producto &p1);
    ~ControlProductosForm();

private slots:
    void on_pushButtonEliminarP_clicked();

    void on_pushButtonVenderP_clicked();

    void on_tableViewProductos_clicked(const QModelIndex &index);

private:
    Ui::ControlProductosForm *ui;
    QSqlTableModel *modeloProducto;  //punteros
    int filaID;
    Producto p1;
};

#endif // CONTROLPRODUCTOSFORM_H
