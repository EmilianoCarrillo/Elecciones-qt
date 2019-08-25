#include "popupcreareleccion.h"
#include "ui_popupcreareleccion.h"
#include <QtDebug>
#include <QSqlError>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>

PopUpCrearEleccion::PopUpCrearEleccion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopUpCrearEleccion)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery qry("SELECT nombre FROM Estado");
    model->setQuery(qry);
    ui->inEntidad->setModel(model);
}

PopUpCrearEleccion::~PopUpCrearEleccion()
{
    delete ui;
}

void PopUpCrearEleccion::on_btnCrear_clicked()
{
    QSqlQuery qry;
    qry.exec("SELECT idEstado FROM Estado WHERE nombre = '"+ ui->inEntidad->currentText()+"'");
    while(qry.next()){
        QString idEstado = qry.value(0).toString();
        QString nombre = ui->inNombre->text();

        QSqlQuery qryCreate;
        qryCreate.prepare("INSERT INTO Eleccion (nombre, fase, tipo) VALUES ('"+ nombre +"', 'abierta', '"+ idEstado +"')");
        qryCreate.exec();

        close();
    }
}
