#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>

namespace Ui {
class adminWin;
}

class adminWin : public QWidget
{
    Q_OBJECT

public:
    explicit adminWin(QWidget *parent = nullptr);
    ~adminWin();

private slots:
    void on_btnCerrarSesion_clicked();

    void on_btnEliminar_clicked();

    void on_btnElecciones_clicked();

    void on_btnVotantes_clicked();

    void on_btnCandidatos_clicked();

    void on_btnCrear_clicked();

    void on_btnEliminarCandidato_clicked();

    void on_btnEliminarVotante_clicked();

    void on_btnAprobar_clicked();

    void on_btnPropuesta_clicked();

    void on_btnCambiarFase_clicked();

private:
    Ui::adminWin *ui;
};

#endif // ADMINWIN_H
