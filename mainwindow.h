#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "usuario.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnRegistrarse_clicked();

    void on_btnIniciarSesion_clicked();

private:
    Ui::MainWindow *ui;
    Usuario *actual;
};

#endif // MAINWINDOW_H
