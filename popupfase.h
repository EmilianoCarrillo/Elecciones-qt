#ifndef POPUPFASE_H
#define POPUPFASE_H

#include <QWidget>

namespace Ui {
class popupFase;
}

class popupFase : public QWidget
{
    Q_OBJECT

public:
    explicit popupFase(QString id, QWidget *parent = nullptr);
    ~popupFase();

private slots:
    void on_btnCambiar_clicked();

private:
    Ui::popupFase *ui;
    QString idEleccion;
};

#endif // POPUPFASE_H
