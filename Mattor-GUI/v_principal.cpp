#include "v_principal.h"
#include "ui_v_principal.h"
#include "v_palabras.h"
#include "v_visualizacion.h"
#include <QMessageBox>

#include <string>

using namespace std;

v_principal::v_principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::v_principal)
{
    ui->setupUi(this);
    c_data = new core;
}

v_principal::~v_principal(){
    delete ui;
}

void v_principal::refreshInfo(){
    char *texto = new char[6];

    sprintf(texto, "%d", c_data->getEstados());
    ui->l_s_estados->setText(texto);
    sprintf(texto, "%d", c_data->getTransiciones());
    ui->l_s_transiciones->setText(texto);
    sprintf(texto, "%d", c_data->getFinales());
    ui->l_s_finales->setText(texto);
}

void v_principal::on_b_inicial_textChanged(){
    // Cambiado a uso de botón
}

void v_principal::on_tt_final_clicked(){
    if( (int) ui->b_final->toPlainText().toStdString().size() == 0) return;

    int n = ui->b_final->toPlainText().toInt();
    char *texto = new char[30];

    if(c_data->addFinal(n)){
        sprintf(texto, "(q%d) agregado.", n);
        refreshInfo();
        ui->b_final->clear();
    }else{
        sprintf(texto, "(q%d) rechazado.", n);
    }
    ui->l_e_final->setText(texto);

}

void v_principal::on_tt_inicial_clicked(){
    if((int) ui->b_inicial->toPlainText().toStdString().size() == 0) return;

    int n = ui->b_inicial->toPlainText().toInt();
    char *texto = new char[20];
    sprintf(texto, ": (q%d)", n);
    ui->l_inicial->setText(texto);

    c_data->setInicial(n);

    refreshInfo();
}

void v_principal::on_tt_tr_clicked(){
    if(
            (int) ui->b_einicial->toPlainText().toStdString().size() == 0 ||
            (int) ui->b_efinal->toPlainText().toStdString().size() == 0
    )
    return;

    int eA = ui->b_einicial->toPlainText().toInt();
    char simb = ui->b_simb->toPlainText().toStdString()[0];
    int eB = ui->b_efinal->toPlainText().toInt();

    char *texto = new char[50];
    if(c_data->addT(eA, simb, eB)){
        sprintf(texto, "(q%d)-[%c]->(q%d) asignado.", eA, simb, eB);

        refreshInfo();
    }else{
        sprintf(texto, "(q%d)-[%c]->(q%d) ya existe.", eA, simb, eB);
    }
    ui->l_e_tr->setText(texto);
}

void v_principal::on_tt_limpiar_clicked(){
    clearAll();
}

void v_principal::clearAll(){
    // Data
    c_data->estados.clear();
    c_data->e_finales.clear();

    // Box de ingreso
    ui->b_einicial->clear();
    ui->b_simb->clear();
    ui->b_efinal->clear();
    ui->b_inicial->clear();
    ui->b_final->clear();

    // Labels de feedback
    ui->l_e_final->setText("");
    ui->l_e_tr->setText("");
    ui->l_inicial->setText("");

    // Tabla central
    refreshInfo();
}

void v_principal::on_tt_finalizar_clicked(){
    // Lleva a la siguiente ventana

    /* Falta de datos */
    bool error = false;
    string cuerpo = "";

    if(c_data->e_inicial == nullptr){
        error = true;
        cuerpo += "- No se ingresó estado inicial.\n";
    }

    if(c_data->getEstados() == 0){
        error = true;
        cuerpo += "- No se ingresó estado(s).\n";
    }

    if(c_data->getTransiciones() == 0){
        error = true;
        cuerpo += "- No se añadió transicion(es).\n";
    }

    if(c_data->getFinales() == 0){
        error = true;
        cuerpo += "- No se ingresó estado(s) final(es).\n";
    }

    if(error){
        char s_cuerpo[cuerpo.size() + 1];
        strcpy(s_cuerpo, cuerpo.c_str());
        QMessageBox::information(this, "Error", s_cuerpo);
        return;
    }

    /* No hay errores: */
    printf("No se encontraron errores.\n");
    v_palabras v(this);
    v.setModal(true);
    v.c_data = c_data;
    v.exec();
}

void v_principal::on_b_simb_textChanged(){
    string simb = ui->b_simb->toPlainText().toStdString();
    if(simb.size() > 1){
        ui->b_simb->document()->setPlainText(QString(simb[0]));
    }
}

void v_principal::on_tt_prev_clicked(){
    v_visualizacion v(this);
    v.setModal(true);
    v.c_data = c_data;
    v.showAutomata();
    v.exec();
}
