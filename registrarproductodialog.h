#ifndef REGISTRARPRODUCTODIALOG_H
#define REGISTRARPRODUCTODIALOG_H

#include <QDialog>
#include "producto.h"

namespace Ui {
class RegistrarProductoDialog;
}

class RegistrarProductoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrarProductoDialog(QWidget *parent = nullptr);
    ~RegistrarProductoDialog();
     Producto getProducto() const {return p1;}

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RegistrarProductoDialog *ui;
    Producto p1;
};

#endif // REGISTRARPRODUCTODIALOG_H
