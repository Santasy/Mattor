#ifndef V_PALABRAS_H
#define V_PALABRAS_H

#include <QDialog>

#include "core.h"

namespace Ui {
class v_palabras;
}

class v_palabras : public QDialog
{
    Q_OBJECT

public:
    explicit v_palabras(QWidget *parent = 0);
    ~v_palabras();
    void addLog(QListWidgetItem *item);
    void addResult(char *texto, bool aceptada);

    /* Atributos */
    core *c_data = nullptr;
    estado *curr = nullptr;

private slots:
    void on_tt_procesar_clicked();

private:
    Ui::v_palabras *ui;
};

#endif // V_PALABRAS_H
