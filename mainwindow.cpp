#include <QStandardItemModel>
#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include "candidatowin.h"
#include "adminwin.h"
#include "mainwindow.h"
#include "registrowin.h"
#include "votantewin.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    actual = new Usuario;

    // SETUP DATABASE     ------------------------------------------------------------
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("localhost");
   db.setDatabaseName("EleccionesBD");
   db.setUserName("root");
   db.setPassword("password");

   if(db.open()){
       qDebug() << "connected " << db.hostName() << db.databaseName();
   } else {
       qDebug() << "Connection FAILED.";
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnRegistrarse_clicked(){
    registroWin *r = new registroWin();
    r->show();
}

void MainWindow::on_btnIniciarSesion_clicked()
{
    QString usuario = ui->inUsuario->text();
    QString contrasena = ui->inContrasena->text();

    if(usuario == "admin" && contrasena == "1234"){
        adminWin *w = new adminWin;
        w->show();
        close();
    } else {
        QSqlQuery qryAuthVot;
        qryAuthVot.exec("SELECT Cuenta.usuario as usuario, contraseña, Persona.nombre as nombre, Persona.CURP as curp, Estado.idEstado as idEstado, Estado.nombre as estado, Votante.idVotante as idVotante FROM Cuenta INNER JOIN Persona ON Cuenta.usuario = Persona.usuario INNER JOIN Estado ON Persona.idEstado = Estado.idEstado INNER JOIN Votante ON Votante.curp = Persona.curp WHERE Cuenta.usuario = '"+usuario+"'");

        if(qryAuthVot.first()){
            //INFO VOTANTE
            actual->usuario     = qryAuthVot.value(0).toString();
            actual->contraseña  = qryAuthVot.value(1).toString();
            actual->nombre      = qryAuthVot.value(2).toString();
            actual->curp        = qryAuthVot.value(3).toString();
            actual->idEstado    = qryAuthVot.value(4).toInt();
            actual->estado      = qryAuthVot.value(5).toString();
            actual->idVotante   = qryAuthVot.value(6).toInt();

            votanteWin *w = new votanteWin(actual);
            w->show();
            close();
        } else{
            QSqlQuery qryAuthCand;
            qryAuthCand.exec("SELECT Cuenta.usuario as usuario, contraseña, Persona.nombre as nombre, Persona.CURP as curp, Estado.idEstado as idEstado, Estado.nombre as estado, Candidato.idCandidato as idCandidato, propuesta, Partido.idPartido as idPartido, Partido.nombre as partido, Eleccion.idEleccion as idEleccion, Eleccion.nombre as eleccion, Eleccion.fase as eleccionFase FROM Cuenta INNER JOIN Persona ON Cuenta.usuario = Persona.usuario INNER JOIN Estado ON Persona.idEstado = Estado.idEstado INNER JOIN Candidato ON Candidato.curp = Persona.curp INNER JOIN Partido ON Partido.idPartido = Candidato.idPartido INNER JOIN Postulacion ON Postulacion.idCandidato = Candidato.idCandidato INNER JOIN Eleccion ON Eleccion.idEleccion =  Postulacion.idEleccion WHERE Cuenta.usuario = '"+ usuario +"'");

            if(qryAuthCand.first()){
                //INFO CANDIDATO
                actual->usuario     = qryAuthCand.value(0).toString();
                actual->contraseña  = qryAuthCand.value(1).toString();
                actual->nombre      = qryAuthCand.value(2).toString();
                actual->curp        = qryAuthCand.value(3).toString();
                actual->idEstado    = qryAuthCand.value(4).toInt();
                actual->estado      = qryAuthCand.value(5).toString();
                actual->idCandidato = qryAuthCand.value(6).toInt();
                actual->propuesta   = qryAuthCand.value(7).toString();
                actual->idPartido   = qryAuthCand.value(8).toInt();
                actual->partido     = qryAuthCand.value(9).toString();
                actual->idEleccion  = qryAuthCand.value(10).toInt();
                actual->eleccion    = qryAuthCand.value(11).toString();
                actual->fase        = qryAuthCand.value(12).toString();

                candidatoWin *w = new candidatoWin(actual);
                w->show();
                close();
            } else{
                QMessageBox msgBox;
                msgBox.setText("La cuenta no existe o su contraseña es incorrecta.");
                msgBox.exec();
            }
        }

    }


}
