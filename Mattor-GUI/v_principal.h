#ifndef V_PRINCIPAL_H
#define V_PRINCIPAL_H

#include <QMainWindow>
#include "core.h"

namespace Ui {
class v_principal;
}

class v_principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit v_principal(QWidget *parent = 0);

    /* Atributos */
    core *c_data = nullptr;

    ~v_principal();
    void refreshInfo();
    void clearAll();

private slots:
    void on_b_inicial_textChanged();

    void on_tt_final_clicked();

    void on_tt_inicial_clicked();

    void on_tt_tr_clicked();

    void on_tt_limpiar_clicked();

    void on_tt_finalizar_clicked();

    void on_b_simb_textChanged();

private:
    Ui::v_principal *ui;
};

#endif // V_PRINCIPAL_H
