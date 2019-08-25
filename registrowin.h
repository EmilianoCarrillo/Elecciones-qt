#ifndef REGISTROWIN_H
#define REGISTROWIN_H

#include <QWidget>

namespace Ui {
class registroWin;
}

class registroWin : public QWidget
{
    Q_OBJECT

public:
    explicit registroWin(QWidget *parent = nullptr);
    ~registroWin();

private slots:
    void on_btnCandidato_clicked();

    void on_brnRegresar_clicked();

    void on_btnVotante_clicked();

    void on_btnRegistrarCand_clicked();

    void on_btnRegistrarVotante_clicked();

private:
    Ui::registroWin *ui;
};

#endif // REGISTROWIN_H
