#ifndef VOTANTEWIN_H
#define VOTANTEWIN_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class votanteWin;
}

class votanteWin : public QWidget
{
    Q_OBJECT

public:
    explicit votanteWin(Usuario *u,QWidget *parent = nullptr);
    ~votanteWin();

private slots:
    void on_btnParticipar_clicked();

    void on_btnCerrarSesion_clicked();

    void on_btnVerResultados_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::votanteWin *ui;
    Usuario *actual;
};

#endif // VOTANTEWIN_H
