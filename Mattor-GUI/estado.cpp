#include "estado.h"

estado::estado(){

}

estado::estado(int n){
    id = n;
}

bool estado::addT(char simb, estado *e_final){
    if(transiciones.find(simb) != transiciones.end() && transiciones.find(simb)->second->id == e_final->id){ // Si es que ya existe la misma transición
        return false;
    }else{ // Cualquier conexión anterior se reemplaza
        transiciones[simb] = e_final;
        return true;
    }
}

int estado::getTransiciones(){
    int sum = 0;
    for(auto x : transiciones) sum += 1;
    return sum;
}
