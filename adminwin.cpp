#include "adminwin.h"
#include "mainwindow.h"
#include "popupcreareleccion.h"
#include "popupfase.h"
#include "ui_adminwin.h"
#include <QDebug>
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>

adminWin::adminWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminWin)
{
    ui->setupUi(this);

    on_btnElecciones_clicked();
}

adminWin::~adminWin()
{
    delete ui;
}

void adminWin::on_btnCerrarSesion_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    close();
}

void adminWin::on_btnElecciones_clicked()
{
    ui->lbl->setText("Gestionar Elecciones");
    ui->btnAprobar->hide();
    ui->btnCambiarFase->show();
    ui->btnCrear->show();
    ui->btnPropuesta->hide();
    ui->btnEliminar->show();
    ui->btnEliminarCandidato->hide();
    ui->btnEliminarVotante->hide();

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery qry("SELECT Eleccion.idEleccion, Eleccion.nombre, Eleccion.fase, Eleccion.tipo AS idDeEstado, Estado.nombre AS entidad FROM Eleccion INNER JOIN Estado ON Estado.idEstado = Eleccion.tipo");
    model->setQuery(qry);
    ui->tbl->setModel(model);

}

void adminWin::on_btnVotantes_clicked()
{
    ui->lbl->setText("Gestionar Votantes");
    ui->btnAprobar->hide();
    ui->btnCambiarFase->hide();
    ui->btnCrear->hide();
    ui->btnPropuesta->hide();
    ui->btnEliminar->hide();
    ui->btnEliminarCandidato->hide();
    ui->btnEliminarVotante->show();

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery qry("SELECT Votante.idVotante, Persona.CURP, Persona.nombre, Estado.nombre AS estado, Cuenta.usuario, Cuenta.contraseña FROM Votante INNER JOIN Persona ON Votante.CURP = Persona.CURP INNER JOIN Cuenta ON Cuenta.usuario = Persona.usuario INNER JOIN Estado ON Estado.idEstado = Persona.idEstado;");
    model->setQuery(qry);
    ui->tbl->setModel(model);
}

void adminWin::on_btnCandidatos_clicked()
{
    ui->lbl->setText("Gestionar Candidatos");
    ui->btnAprobar->show();
    ui->btnCambiarFase->hide();
    ui->btnCrear->hide();
    ui->btnPropuesta->show();
    ui->btnEliminar->hide();
    ui->btnEliminarCandidato->show();
    ui->btnEliminarVotante->hide();

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery qry("SELECT Candidato.idCandidato, Persona.nombre,  Eleccion.nombre AS eleccion, Eleccion.fase, Estado.nombre AS área, Candidato.propuesta, Persona.CURP, Cuenta.usuario, Cuenta.contraseña FROM Candidato INNER JOIN Persona ON Candidato.CURP = Persona.CURP INNER JOIN Cuenta ON Cuenta.usuario = Persona.usuario INNER JOIN Postulacion ON Postulacion.idCandidato = Candidato.idCandidato INNER JOIN Eleccion ON Eleccion.idEleccion = Postulacion.idEleccion INNER JOIN Estado ON Estado.idEstado = Eleccion.tipo");
    model->setQuery(qry);
    ui->tbl->setModel(model);

}

void adminWin::on_btnPropuesta_clicked()
{
    int selectedRow = ui->tbl->selectionModel()->selectedRows()[0].row();
    QString propuesta = ui->tbl->model()->index(selectedRow, 5).data().toString();

    if(selectedRow > -1){
        QMessageBox msgBox;
        msgBox.setText(propuesta);
        msgBox.exec();
    }
}

void adminWin::on_btnCrear_clicked()
{
    PopUpCrearEleccion *w = new PopUpCrearEleccion;
    w->show();
}

void adminWin::on_btnEliminar_clicked()
{
    int selectedRow = ui->tbl->selectionModel()->selectedRows()[0].row();
    QString idEleccion = ui->tbl->model()->index(selectedRow, 0).data().toString();

    QSqlQuery qry("DELETE FROM Eleccion WHERE (idEleccion = '"+ idEleccion +"')");

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmación", ("¿Está seguro de que desea eliminar la eleccion "+ idEleccion +"?"),
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
          qry.exec();
          on_btnElecciones_clicked();
    }

}

void adminWin::on_btnEliminarCandidato_clicked()
{
    int selectedRow = ui->tbl->selectionModel()->selectedRows()[0].row();
    QString idCandidato = ui->tbl->model()->index(selectedRow, 0).data().toString();

    QSqlQuery qry("DELETE FROM Candidato WHERE (idCandidato = '"+ idCandidato +"')");

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmación", ("¿Está seguro de que desea eliminar al Candidato "+ idCandidato +"?"),
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
          qry.exec();
          on_btnCandidatos_clicked();
    }
}

void adminWin::on_btnEliminarVotante_clicked()
{
    int selectedRow = ui->tbl->selectionModel()->selectedRows()[0].row();
    QString idVotante = ui->tbl->model()->index(selectedRow, 0).data().toString();

    QSqlQuery qry("DELETE FROM Votante WHERE (idVotante = '"+ idVotante +"')");

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmación", ("¿Está seguro de que desea eliminar al Votante "+ idVotante +"?"),
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
          qry.exec();
          on_btnVotantes_clicked();
    }
}

void adminWin::on_btnAprobar_clicked()
{
    int selectedRow = ui->tbl->selectionModel()->selectedRows()[0].row();
    QString nombre = ui->tbl->model()->index(selectedRow, 1).data().toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmación", ("¿ Desea aprobar los documentos de "+ nombre +"?"),
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QMessageBox msgBox;
        msgBox.setText("El candidato ya puede ingresar a su cuenta");
        msgBox.exec();
    }
}



void adminWin::on_btnCambiarFase_clicked()
{
    int selectedRow = ui->tbl->selectionModel()->selectedRows()[0].row();
    QString idEleccion = ui->tbl->model()->index(selectedRow, 0).data().toString();

    popupFase *w = new popupFase(idEleccion);
    w->show();
}
