#ifndef MODIFICARPRODUCTODIALOG_H
#define MODIFICARPRODUCTODIALOG_H

#include <QDialog>
#include "producto.h"

namespace Ui {
class ModificarProductoDialog;
}

class ModificarProductoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModificarProductoDialog(QWidget *parent = nullptr);
    Producto getProducto() const {return p2;}
    ~ModificarProductoDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ModificarProductoDialog *ui;
    Producto p2;
};

#endif // MODIFICARPRODUCTODIALOG_H
