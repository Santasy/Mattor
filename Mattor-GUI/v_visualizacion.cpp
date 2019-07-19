#include "v_visualizacion.h"
#include "ui_v_visualizacion.h"

v_visualizacion::v_visualizacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::v_visualizacion)
{
    ui->setupUi(this);
}

v_visualizacion::~v_visualizacion()
{
    delete ui;
}

void v_visualizacion::showAutomata(){
    string texto = "";
    char *linea = new char[50];

    // Datos generales:

    sprintf(linea, "N° de Estados: %d\n", c_data->getEstados());
    texto += linea;
    sprintf(linea, "Transiciones: %d\n", c_data->getTransiciones());
    texto += linea;
    sprintf(linea, "Estados Finales: %d\n", c_data->getFinales());
    texto += linea;
    texto += "|-------------|\n\n";

    // Transiciones:
    texto += "Transiciones:\n";
    estado *e = nullptr;
    for(auto x : c_data->estados){
        e = &(x.second);

        // Estado inicial:
        if(c_data->isFinal(e->id)){
            sprintf(linea, "((q%d)): ", e->id);
        }else{
            sprintf(linea, " (q%d) : ", e->id);
        }
        texto += linea;

        // Transiciones:
        for(auto y : e->transiciones){
            if(c_data->isFinal(y.second->id)){
                sprintf(linea, " [%c]-> ((q%d)) | ", y.first, y.second->id);
            }else{
                sprintf(linea, " [%c]->  (q%d)  | ", y.first, y.second->id);
            }
            texto += linea;
        }
        texto += "\n";
    }

    // Finalizando:
    char s_final[texto.size() + 1];
    strcpy(s_final, texto.c_str());
    ui->l_visual->setText(s_final);
    ui->l_visual->adjustSize();
    ui->groupBox->adjustSize();
    adjustSize();
}
