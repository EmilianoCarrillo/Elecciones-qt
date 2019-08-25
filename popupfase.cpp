#include "popupfase.h"
#include "ui_popupfase.h"
#include <QtDebug>
#include <QSqlError>
#include <qsqlquery.h>

popupFase::popupFase(QString id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::popupFase)
{
    ui->setupUi(this);
    idEleccion = id;
}

popupFase::~popupFase()
{
    delete ui;
}

void popupFase::on_btnCambiar_clicked()
{
    QSqlQuery qry;
    qry.exec("UPDATE Eleccion SET fase = '"+ ui->inFase->currentText() +"' WHERE (idEleccion = '"+ idEleccion +"')");
    qDebug() << qry.lastError();
    close();
}
