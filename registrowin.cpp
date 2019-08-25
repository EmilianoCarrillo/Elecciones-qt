#include "registrowin.h"
#include "ui_registrowin.h"
#include <QDebug>
#include <QSqlError>
#include <qmessagebox.h>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>

registroWin::registroWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registroWin)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery qry("SELECT nombre FROM Estado");
    model->setQuery(qry);
    ui->inEstado->setModel(model);
    ui->inEstadoCand->setModel(model);

    QSqlQueryModel *model2 = new QSqlQueryModel;
    QSqlQuery qry2("SELECT nombre FROM Partido");
    model2->setQuery(qry2);
    ui->inPartido->setModel(model2);

    QSqlQueryModel *model3 = new QSqlQueryModel;
    QSqlQuery qry3("SELECT nombre FROM Eleccion");
    model3->setQuery(qry3);
    ui->inEleccion->setModel(model3);

}

registroWin::~registroWin()
{
    delete ui;
}

void registroWin::on_btnCandidato_clicked()
{
    ui->sw->setCurrentIndex(1);
}

void registroWin::on_brnRegresar_clicked()
{
    close();
}

void registroWin::on_btnVotante_clicked()
{
    ui->sw->setCurrentIndex(0);
}

void registroWin::on_btnRegistrarCand_clicked()
{

    if(ui->sw->currentIndex() == 0){
        // Registrar Usuario
        // Registrar Persona
        // Registrar candidato
        // Registrar Postulacion

        QString nombreCand = ui->inNombreCand->text();
        QString estadoCand = ui->inEstadoCand->currentText();
        QString partido = ui->inPartido->currentText();
        QString eleccion = ui->inEleccion->currentText();
        QString curpCand = ui->inCurpCand->text();
        QString propuesta = ui->inPropuesta->toPlainText();
        QString usuarioCand = curpCand.left(6);
        QString contraseñaCand = QString::number(rand()%(9999-1000 + 1) + 1000);
        QString idEstado, idPartido, idEleccion, idCandidato;

        QSqlQuery qryEstado;
        qryEstado.exec("SELECT idEstado FROM Estado WHERE nombre = '"+ estadoCand +"'");
        while(qryEstado.next()){
            idEstado = qryEstado.value(0).toString();
        }

        QSqlQuery qryEleccion;
        qryEleccion.exec("SELECT idEleccion FROM Eleccion WHERE nombre = '"+ eleccion +"'");
        while(qryEleccion.next()){
            idEleccion = qryEleccion.value(0).toString();
        }

        QSqlQuery qryPartido;
        qryPartido.exec("SELECT idPartido FROM Partido WHERE nombre = '"+ partido +"'");
        while(qryPartido.next()){
            idPartido = qryPartido.value(0).toString();
        }

        QSqlQuery qryCrearCuenta;
        qryCrearCuenta.prepare("INSERT INTO Cuenta (usuario, contraseña) VALUES ('"+ usuarioCand +"', '"+ contraseñaCand +"')");
        qryCrearCuenta.exec();

        QSqlQuery qryCrearPersona;
        qryCrearPersona.prepare("INSERT INTO Persona (CURP, nombre, usuario, idEstado) VALUES ('"+curpCand +"', '"+ nombreCand +"', '"+ usuarioCand +"', '"+ idEstado +"')");
        qryCrearPersona.exec();

        QSqlQuery qryCrearCandidato;
        qryCrearCandidato.prepare("INSERT INTO Candidato (propuesta, CURP, idPartido) VALUES ('"+ propuesta +"', '"+ curpCand +"', '"+ idPartido +"');");
        qryCrearCandidato.exec();

        QSqlQuery qryCandidato;
        qDebug() << nombreCand << endl;
        qryCandidato.exec("SELECT idCandidato FROM Candidato WHERE curp = '"+ curpCand +"'");
        while(qryCandidato.next()){
            idCandidato = qryCandidato.value(0).toString();
            qDebug() << idCandidato<< endl;
        }

        qDebug() << idEleccion << endl << idCandidato;
        QSqlQuery qryCrearPostulacion;
        qryCrearPostulacion.prepare("INSERT INTO Postulacion (idEleccion, idCandidato) VALUES ('"+ idEleccion +"', '"+ idCandidato +"')");
        qryCrearPostulacion.exec();

        QMessageBox msgBox;
        msgBox.setText("Tu usario es: " + usuarioCand + "\n tu contraseña: " + contraseñaCand);
        msgBox.exec();
        close();

    }
}

void registroWin::on_btnRegistrarVotante_clicked()
{
    //Registrar cuenta
    //Registrar persona
    //Registrar votante

    QString nombre = ui->inNombre->text();
    QString estado = ui->inEstado->currentText();
    QString curp = ui->inCurp->text();
    QString usuario = curp.left(6);
    QString contraseña = QString::number(rand()%(9999-1000 + 1) + 1000);
    QString idEstado;

    QSqlQuery qryEstado;
    qryEstado.exec("SELECT idEstado FROM Estado WHERE nombre = '"+ estado +"'");
    while(qryEstado.next()){
        idEstado = qryEstado.value(0).toString();
    }

    QSqlQuery qryCrearCuenta;
    qryCrearCuenta.prepare("INSERT INTO Cuenta (usuario, contraseña) VALUES ('"+ usuario +"', '"+ contraseña +"')");
    qryCrearCuenta.exec();

    QSqlQuery qryCrearPersona;
    qryCrearPersona.prepare("INSERT INTO Persona (CURP, nombre, usuario, idEstado) VALUES ('"+curp +"', '"+ nombre +"', '"+ usuario +"', '"+ idEstado +"')");
    qryCrearPersona.exec();

    QSqlQuery qryCrearVotante;
    qryCrearVotante.prepare("INSERT INTO Votante (CURP) VALUES ('"+curp+"')");
    qryCrearVotante.exec();

    QMessageBox msgBox;
    msgBox.setText("Tu usario es: " + usuario + "\n tu contraseña: " + contraseña);
    msgBox.exec();
    close();
}
