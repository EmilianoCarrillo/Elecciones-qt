#ifndef VOTACIONWIN_H
#define VOTACIONWIN_H

#include "usuario.h"

#include <QWidget>

namespace Ui {
class votacionWin;
}

class votacionWin : public QWidget
{
    Q_OBJECT

public:
    explicit votacionWin(int i, Usuario *a, QWidget *parent = nullptr);
    ~votacionWin();

private slots:
    void on_btnCerrarSesion_clicked();

    void on_btnAtras_clicked();

    void on_btnPropuestas_clicked();

    void on_btnVotar_clicked();

private:
    Ui::votacionWin *ui;
    int idEleccion;
    Usuario *actual;
};

#endif // VOTACIONWIN_H
