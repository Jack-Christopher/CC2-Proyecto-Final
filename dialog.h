#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "vendedor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    bool getIsAdmin();
    void saludar();
    ~Dialog();

private slots:
    void on_buttonBoxLogin_accepted();

    void on_buttonBoxLogin_rejected();

private:
    Ui::Dialog *ui;
    bool isAdmin;
    QVector<std::tuple<QString,QString,QString>> secuenciaDeUsuarios;
};
#endif // DIALOG_H
