#include "v_palabras.h"
#include "ui_v_palabras.h"

v_palabras::v_palabras(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::v_palabras)
{
    ui->setupUi(this);
        // Headers tabla de resultados:
    ui->t_resultados->setColumnCount(2);
    QTableWidgetItem *nItem = new QTableWidgetItem();
    nItem->setText("Resultado");
    ui->t_resultados->setHorizontalHeaderItem(0, nItem);
    nItem = new QTableWidgetItem();
    nItem->setText("Palabra");
    ui->t_resultados->setHorizontalHeaderItem(1, nItem);

        // Lock de tamaños:
    //  Primera columna más pequeña:
    ui->t_resultados->setColumnWidth(0, 80);
    ui->t_resultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->t_resultados->setRowCount(0); // Limpia las líneas
}

v_palabras::~v_palabras()
{
    delete ui;
}

void v_palabras::on_tt_procesar_clicked(){
    if( (int) ui->b_palabra->toPlainText().toStdString().size() == 0) return;

        // Obtiene palabra de box:
    char *palabra = new char[100];
    strcpy(palabra, ui->b_palabra->toPlainText().toStdString().c_str());

        // Filtros:
    if((int) palabra[0] == 0){ // Palabra vacía
        printf("Palabra vacía.\n");
        return;
    }

        // Se lee la palabra:
    printf("Se leerá palabra %s\n", palabra);
    ui->l_ejecucion->clear(); // Limpia tabla de log

    QListWidgetItem *item;
    bool aceptada = c_data->checkWord(
        palabra,            // Palabra original
        c_data->e_inicial,  // Dirección de memoria del primer nodo (inicial)
        ui->l_ejecucion     // Referencia a la tabla de log
    ); // Se procesa la palabra

    if(aceptada){ // Si la palabra se aceptó
        item = new QListWidgetItem("Palabra aceptada.");
        item->setBackground(Qt::green);
    }else{ // Si no se aceptó
        item = new QListWidgetItem("Palabra no aceptada.");
        item->setBackground(Qt::red);
    }
    addLog(item);
    addResult(palabra, aceptada);
}

void v_palabras::addLog(QListWidgetItem *item){
    ui->l_ejecucion->addItem(item);
    ui->l_ejecucion->scrollToBottom();
}

void v_palabras::addResult(char *texto, bool aceptada){
        int nRow = ui->t_resultados->rowCount();
            // Agrega palabra:
        ui->t_resultados->insertRow(nRow);
        QTableWidgetItem *item = new QTableWidgetItem(texto);
        ui->t_resultados->setItem(nRow, 1, item);

            // Color de resultado:
        item = new QTableWidgetItem("");
        if(aceptada){
            item->setBackground(Qt::green);
        }else{
            item->setBackground(Qt::red);
        }
            // Agrega:
        ui->t_resultados->setItem(nRow, 0, item);
        ui->t_resultados->scrollToBottom();
}
