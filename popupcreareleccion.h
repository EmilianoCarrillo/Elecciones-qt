#ifndef POPUPCREARELECCION_H
#define POPUPCREARELECCION_H

#include <QWidget>

namespace Ui {
class PopUpCrearEleccion;
}

class PopUpCrearEleccion : public QWidget
{
    Q_OBJECT

public:
    explicit PopUpCrearEleccion(QWidget *parent = nullptr);
    ~PopUpCrearEleccion();

private slots:
    void on_btnCrear_clicked();

private:
    Ui::PopUpCrearEleccion *ui;
};

#endif // POPUPCREARELECCION_H
