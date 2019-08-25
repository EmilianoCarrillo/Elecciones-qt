#ifndef RESULTADOSWIN_H
#define RESULTADOSWIN_H

#include <QWidget>

namespace Ui {
class resultadosWin;
}

class resultadosWin : public QWidget
{
    Q_OBJECT

public:
    explicit resultadosWin(int i, QWidget *parent = nullptr);
    ~resultadosWin();

private slots:
    void on_btnCerrarSesion_clicked();

    void on_btnAtras_clicked();

private:
    Ui::resultadosWin *ui;
    int idEleccion;
};

#endif // RESULTADOSWIN_H
