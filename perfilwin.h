#ifndef PERFILWIN_H
#define PERFILWIN_H

#include <QWidget>

namespace Ui {
class perfilWin;
}

class perfilWin : public QWidget
{
    Q_OBJECT

public:
    explicit perfilWin(QWidget *parent = nullptr);
    ~perfilWin();

private slots:
    void on_btnCerrarSesion_clicked();

private:
    Ui::perfilWin *ui;
};

#endif // PERFILWIN_H
