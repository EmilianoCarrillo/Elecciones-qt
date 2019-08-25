#include "votantewin.h"
#include "ui_votantewin.h"
#include "votacionwin.h"
#include "mainwindow.h"
#include "resultadoswin.h"
#include <QSqlQueryModel>
#include <QtDebug>
#include <qsqlquery.h>


votanteWin::votanteWin(Usuario *u, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::votanteWin)
{
    actual = u;
    ui->setupUi(this);

    // Setup labels
    ui->lblNombre->setText(actual->nombre);

    //Setup tables
    QSqlQueryModel *modelEleccionesAbiertas = new QSqlQueryModel;
    QSqlQuery qryEleccionesAbiertas("SELECT * FROM Eleccion LEFT JOIN ( SELECT idEleccion  FROM Votos WHERE idVotante = "+ QString::number(actual->idVotante) +" ) AS tabla ON Eleccion.idEleccion = tabla.idEleccion WHERE ((Eleccion.tipo = "+ QString::number(actual->idEstado) +" OR Eleccion.tipo = 0) AND Eleccion.fase = 'abierta') AND tabla.idEleccion is null");
    modelEleccionesAbiertas->setQuery(qryEleccionesAbiertas);
    ui->tblAbiertas->setModel(modelEleccionesAbiertas);

    QSqlQueryModel *modelEleccionesCerradas = new QSqlQueryModel;
    QSqlQuery qryEleccionesCerradas("SELECT Eleccion.idEleccion, Eleccion.nombre, Eleccion.fase, Estado.nombre as estado FROM Eleccion LEFT JOIN Estado ON Estado.idEstado = Eleccion.tipo WHERE (Estado.idEstado = '"+ QString::number(actual->idEstado) +"' OR Estado.idEstado = 0) AND Eleccion.fase = 'cerrada'");
    modelEleccionesCerradas->setQuery(qryEleccionesCerradas);
    ui->tblResultados->setModel(modelEleccionesCerradas);

    QSqlQueryModel *modelEleccionesEspera = new QSqlQueryModel;
    QSqlQuery qryEleccionesEspera("SELECT Eleccion.idEleccion, Eleccion.nombre, Eleccion.fase, Estado.nombre as estado FROM Eleccion LEFT JOIN Estado ON Estado.idEstado = Eleccion.tipo INNER JOIN Votos ON Votos.idEleccion = Eleccion.idEleccion INNER JOIN Votante ON Votante.idVotante = Votos.idVotante WHERE ((Estado.idEstado = '"+ QString::number(actual->idEstado) +"' OR Estado.idEstado IS NULL) AND Eleccion.fase = 'abierta') AND Votante.idVotante = "+ QString::number(actual->idVotante));
    modelEleccionesEspera->setQuery(qryEleccionesEspera);
    ui->tblEspera->setModel(modelEleccionesEspera);

}

votanteWin::~votanteWin()
{
    delete ui;
}

void votanteWin::on_btnParticipar_clicked()
{
    int selectedRow = ui->tblAbiertas->selectionModel()->selectedRows()[0].row();
    int idEleccion = ui->tblAbiertas->model()->index(selectedRow, 0).data().toInt();

    if(selectedRow > -1){
        votacionWin *w = new votacionWin(idEleccion, actual);
        w->show();
    }
}

void votanteWin::on_btnCerrarSesion_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    close();
}

void votanteWin::on_btnVerResultados_clicked()
{
    int selectedRow = ui->tblResultados->selectionModel()->selectedRows()[0].row();
    int idEleccion = ui->tblResultados->model()->index(selectedRow, 0).data().toInt();

    if(selectedRow > -1){
        resultadosWin *w = new resultadosWin(idEleccion);
        w->show();
    }

}

void votanteWin::on_btnRefresh_clicked()
{
    votanteWin *w = new votanteWin(actual);
    w->show();
    close();
}
