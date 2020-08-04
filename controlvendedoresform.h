#ifndef CONTROLVENDEDORESFORM_H
#define CONTROLVENDEDORESFORM_H

#include <QWidget>

namespace Ui {
class ControlVendedoresForm;
}

class QSqlTableModel;

class ControlVendedoresForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlVendedoresForm(QWidget *parent = nullptr);
    void configurarTabla();
    int getFilaID();
    static void givePrivilegios(int fila);
    static void removePrivilegios(int fila);

    ~ControlVendedoresForm();

private slots:
    void on_pushButtonEliminarU_clicked();

    void on_pushButtonCambiarPrivilegios_clicked();

    void on_tableViewVendedor_clicked(const QModelIndex &index);

private:
    Ui::ControlVendedoresForm *ui;
    QSqlTableModel *modeloVendedor;
    int filaID;
};

#endif // CONTROLVENDEDORESFORM_H
