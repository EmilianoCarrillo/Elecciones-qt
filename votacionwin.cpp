#include "votacionwin.h"
#include "ui_votacionwin.h"
#include "mainwindow.h"
#include <QtDebug>

#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>

votacionWin::votacionWin(int i, Usuario *a, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::votacionWin)
{
    idEleccion = i;
    actual = a;

    ui->setupUi(this);
    ui->lblNombre->setText(a->nombre);

    // TABLE SETUP
    QSqlQueryModel *modelVotaciones = new QSqlQueryModel;
    QSqlQuery qryVotaciones("SELECT Postulacion.idEleccion, Candidato.idCandidato, Persona.nombre as candidato, Partido.nombre as partido, Candidato.propuesta  FROM Postulacion INNER JOIN Candidato ON Candidato.idCandidato = Postulacion.idCandidato INNER JOIN Persona ON Persona.CURP = Candidato.CURP INNER JOIN Partido ON Partido.idPartido = Candidato.idPartido WHERE Postulacion.idEleccion = " + QString::number(idEleccion));
    modelVotaciones->setQuery(qryVotaciones);
    ui->tblCandidatos->setModel(modelVotaciones);

    // LABEL SETUP
    QSqlQuery qryNombreEleccion;
    qryNombreEleccion.exec("SELECT nombre FROM Eleccion WHERE idEleccion = " + QString::number(idEleccion));

    if(qryNombreEleccion.first()){
        ui->lblEleccion->setText(qryNombreEleccion.value(0).toString());
    }

}

votacionWin::~votacionWin()
{
    delete ui;
}

void votacionWin::on_btnCerrarSesion_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    close();
}

void votacionWin::on_btnAtras_clicked()
{
    close();
}

void votacionWin::on_btnPropuestas_clicked()
{
    int selectedRow = ui->tblCandidatos->selectionModel()->selectedRows()[0].row();
    QString propuesta = ui->tblCandidatos->model()->index(selectedRow, 4).data().toString();

    if(selectedRow > -1){
        QMessageBox msgBox;
        msgBox.setText(propuesta);
        msgBox.exec();
    }
}

void votacionWin::on_btnVotar_clicked()
{
    int selectedRow = ui->tblCandidatos->selectionModel()->selectedRows()[0].row();
    QString propuesta = ui->tblCandidatos->model()->index(selectedRow, 4).data().toString();

    if(selectedRow > -1){
        QString idVotante = QString::number(actual->idVotante);
        QString idEleccion = ui->tblCandidatos->model()->index(selectedRow, 0).data().toString();
        QString idCandidato = ui->tblCandidatos->model()->index(selectedRow, 1).data().toString();
        QString candidato = ui->tblCandidatos->model()->index(selectedRow, 2).data().toString();


        QSqlQuery qryVotacion("INSERT INTO Votos (idVotante, idEleccion, idCandidato) VALUES ("+ idVotante +", "+ idEleccion +", "+ idCandidato +")");

        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Confirmación", ("¿Está seguro de que desea votar por "+ candidato +"?"),
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
              qryVotacion.exec();
              close();
          }

    }
}
