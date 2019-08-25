#include "candidatowin.h"
#include "mainwindow.h"
#include "resultadoswin.h"
#include "ui_candidatowin.h"
#include <QtCore>
#include <QSqlError>
#include <qsqlquery.h>
#include <qmessagebox.h>

candidatoWin::candidatoWin(Usuario *u, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::candidatoWin)
{
    actual = u;
    ui->setupUi(this);

    ui->lblNombre->setText(actual->nombre);
    ui->lblEleccion->setText(actual->eleccion);
    ui->lblEstado->setText(actual->estado);
    ui->lblPartido->setText(actual->partido);
    ui->lblPropuesta->setPlainText(actual->propuesta);
}

candidatoWin::~candidatoWin()
{
    delete ui;
}

void candidatoWin::on_btnCerrarSesion_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    close();
}

void candidatoWin::on_btnVerResultados_clicked()
{

    QSqlQuery qryResultados;
    qryResultados.exec("SELECT Eleccion.fase FROM Eleccion WHERE Eleccion.idEleccion = " + QString::number(actual->idEleccion));

    if(qryResultados.first()){
        QString fase = qryResultados.value(0).toString();

        if(fase == "cerrada"){
            resultadosWin *w = new resultadosWin(actual->idEleccion);
            w->show();
        } else{
            QMessageBox msgBox;
            msgBox.setText("Los resultados aún no se encuentran disponibles.");
            msgBox.exec();
        }

    } else{
        qDebug() << qryResultados.lastError();
    }

}
