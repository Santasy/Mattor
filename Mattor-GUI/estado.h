#ifndef ESTADO_H
#define ESTADO_H

#include <vector>
#include <unordered_map>

using namespace std;

class estado{
public:
    /* Atributos */
    int id; // Al parecer, innecesario.
    unordered_map<char, estado*> transiciones;

    /* Funciones */
    estado();
    estado(int n);
    bool addT(char simb, estado *e_final);

    int getTransiciones();
};

#endif // ESTADO_H
