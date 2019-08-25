#include "mainwindow.h"
#include "perfilwin.h"
#include "ui_perfilwin.h"

perfilWin::perfilWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::perfilWin)
{
    ui->setupUi(this);
}

perfilWin::~perfilWin()
{
    delete ui;
}

void perfilWin::on_btnCerrarSesion_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    close();
}
