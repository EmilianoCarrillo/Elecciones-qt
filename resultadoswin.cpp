#include "mainwindow.h"
#include "resultadoswin.h"
#include "ui_resultadoswin.h"
#include <QtCore>
#include <qsqlquery.h>
#include <QSqlError>
#include <qsqlquerymodel.h>

resultadosWin::resultadosWin(int i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resultadosWin)
{
    idEleccion = i;
    ui->setupUi(this);

    // Setup labels
    QSqlQuery qryResultados;
    qryResultados.exec("SELECT cantidadVotos, Partido.nombre, Persona.nombre, propuesta, Eleccion.nombre FROM (SELECT Votos.idCandidato, COUNT(Votos.idCandidato) as cantidadVotos FROM Eleccion INNER JOIN Votos ON Votos.idEleccion = Eleccion.idEleccion GROUP BY Votos.idCandidato ORDER BY cantidadVotos DESC) AS tabla INNER JOIN Candidato ON Candidato.idCandidato = tabla.idCandidato INNER JOIN Partido  ON Partido.idPartido = Candidato.idPartido INNER JOIN Persona ON Persona.CURP = Candidato.CURP INNER JOIN Postulacion ON Postulacion.idCandidato = Candidato.idCandidato INNER JOIN Eleccion ON Eleccion.idEleccion = Postulacion.idEleccion WHERE Eleccion.idEleccion = " + QString::number(idEleccion));

    if(qryResultados.first()){
        //INFO GANADOR
        ui->lblCandidato->setText(qryResultados.value(2).toString());
        ui->lblEleccion->setText(qryResultados.value(4).toString());
        ui->lblPartido->setText(qryResultados.value(1).toString());
        ui->lblPropuesta->setText(qryResultados.value(3).toString());
    } else{
        qDebug() << qryResultados.lastError();
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery qry("SELECT cantidadVotos AS '# Votos', Persona.nombre AS candidato, Partido.nombre AS partido, Postulacion.idEleccion FROM  (SELECT Votos.idCandidato, COUNT(Votos.idCandidato) as cantidadVotos FROM Eleccion INNER JOIN Votos ON Votos.idEleccion = Eleccion.idEleccion GROUP BY Votos.idCandidato ORDER BY cantidadVotos DESC) AS tabla INNER JOIN Candidato ON Candidato.idCandidato = tabla.idCandidato INNER JOIN Persona ON Candidato.CURP = Persona.CURP INNER JOIN Partido ON Partido.idPartido = Candidato.idPartido INNER JOIN Postulacion ON Postulacion.idCandidato = Candidato.idCandidato INNER JOIN Eleccion ON Eleccion.idEleccion = Postulacion.idEleccion WHERE Eleccion.idEleccion = "+ QString::number(idEleccion) +" ORDER BY cantidadVotos DESC;");
    model->setQuery(qry);
    ui->tblResults->setModel(model);
}

resultadosWin::~resultadosWin()
{
    delete ui;
}

void resultadosWin::on_btnCerrarSesion_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    close();
}

void resultadosWin::on_btnAtras_clicked()
{
    close();
}
