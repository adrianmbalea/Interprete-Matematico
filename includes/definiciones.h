#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include "comandos.h"

union Valor {
    double var;
    double (*funcptr)();
    void (*cmdptr)();
};

typedef struct {
    char *lexema;
    int compLex;
    union Valor valor;
} componente;

extern const componente palabrasReservadas[];
extern int imprimirResultados;

#endif /* DEFINICIONES_H */