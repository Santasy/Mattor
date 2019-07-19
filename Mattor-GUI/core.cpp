#include "core.h"

#include <iostream>

core::core(){

}

bool core::create(int n){
    estado nuevo(n);
    estados[n] = nuevo;
    printf("Se ha creado q%d.\n", n);
    return true;
}

bool core::checkWord(char *palabra, estado *curr, QListWidget *lista){

    if((int) palabra[0] != 0){ // No se ha llegado al fin de la palabra
        char *texto = new char[100];
        char *final = new char[100];
        QListWidgetItem *item = new QListWidgetItem();

        if(isFinal(curr->id)){
            sprintf(texto, "(( q%d )) ", curr->id);
        }else{
            sprintf(texto, " ( q%d )  ", curr->id);
        }

        /* Casos para el avance */
        if(curr->transiciones.find(palabra[0]) == curr->transiciones.end()){ // Si es que no hay transición
            strcat(texto, "X");
            item->setForeground(Qt::red);
            item->setText(texto);
            lista->addItem(item);
            lista->scrollToBottom();
            return false;
        }else{
            estado *enlace = curr->transiciones.find(palabra[0])->second;
            if(isFinal(enlace->id)){
                sprintf(final, "-[%c]-> (( q%d ))", palabra[0], enlace->id);
                item->setForeground(Qt::blue);
            }else{
                sprintf(final, "-[%c]->  ( q%d ) ", palabra[0], enlace->id);
            }
            strcat(texto, final);
            item->setText(texto);
            lista->addItem(item);
            lista->scrollToBottom();
            return checkWord(palabra + 1, enlace, lista);
        }
    }else{ // Se leyó la palabra completa
        printf("Finalizando en q%d\n", curr->id);
        return isFinal(curr->id);
    }
}

bool core::isFinal(int n){
    for(int i = 0; i < (int) e_finales.size(); ++i){
        if(n == e_finales[i]) return true;
    }
    return false;
}

bool core::setInicial(int n){
    if(estados.find(n) == estados.end()){
        create(n);
    }
    e_inicial = &(estados.find(n)->second);
    printf("Se ha establecido q%d como estado inicial.\n", n);
    return true;
}

bool core::addFinal(int n){
    if(estados.find(n) == estados.end() || isFinal(n)){
        return false;
    }else{
        e_finales.push_back(n);
        return true;
    }
}

bool core::addT(int eA, char simb, int eB){
        // Comprueba que existan
    if(estados.find(eA) == estados.end()){
        create(eA);
    }
    if(estados.find(eB) == estados.end()){
        create(eB);
    }
        // Crea la conexión
    estado *e_A = &(estados.find(eA)->second);
    estado *e_B = &(estados.find(eB)->second);

    return e_A->addT(simb, e_B);
}

int core::getEstados(){
    int sum = 0;
    for(auto it : estados) sum += 1;
    return sum;
}

int core::getTransiciones(){
    int sum = 0;
    for(auto it : estados){
        sum += it.second.getTransiciones();
    }
    return sum;
}

int core::getFinales(){
    return (int) e_finales.size();
}
