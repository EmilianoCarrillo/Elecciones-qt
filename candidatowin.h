#ifndef CANDIDATOWIN_H
#define CANDIDATOWIN_H

#include "usuario.h"

#include <QWidget>

namespace Ui {
class candidatoWin;
}

class candidatoWin : public QWidget
{
    Q_OBJECT

public:
    explicit candidatoWin(Usuario *u, QWidget *parent = nullptr);
    ~candidatoWin();

private slots:
    void on_btnCerrarSesion_clicked();

    void on_btnVerResultados_clicked();

private:
    Ui::candidatoWin *ui;
    Usuario *actual;
};

#endif // CANDIDATOWIN_H
