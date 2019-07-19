#ifndef CORE_H
#define CORE_H

#include "estado.h"
#include <unordered_map>
#include <vector>
#include <QListWidget>

using namespace std;

class core{
public:
    /* Atributos */
    unordered_map<int, estado> estados; // Estructura para nodos
    estado *e_inicial = nullptr;
    vector<int> e_finales;

    /* Funciones */
    core();
    bool create(int n);
    bool setInicial(int n);
    bool addFinal(int n);
    bool addT(int eA, char simb, int eB);

    bool isFinal(int n);

    int getEstados();
    int getTransiciones();
    int getFinales();

    bool checkWord(char *palabra, estado *curr, QListWidget *lista);
};

#endif // core_H
