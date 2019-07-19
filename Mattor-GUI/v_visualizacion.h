#ifndef V_VISUALIZACION_H
#define V_VISUALIZACION_H

#include <QDialog>

#include "core.h"

namespace Ui {
class v_visualizacion;
}

class v_visualizacion : public QDialog
{
    Q_OBJECT

public:
    explicit v_visualizacion(QWidget *parent = 0);
    ~v_visualizacion();
    void showAutomata();

    core *c_data = nullptr;
private:
    Ui::v_visualizacion *ui;
};

#endif // V_VISUALIZACION_H
