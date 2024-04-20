#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include "comandos.h"

#define VAR 300
#define CONST 301
#define FUNC 302
#define COMENTARIO 303
#define NUMERO 304
#define MENOR_IGUAL 305
#define MAYOR_IGUAL 306
#define IGUAL_IGUAL 307
#define DISTINTO 308
#define MAS_IGUAL 309
#define MENOS_IGUAL 310
#define POR_IGUAL 311
#define SLASH_IGUAL 312
#define PORCENTAJE_IGUAL 313

union Valor {
    double var;
    double (*funcptr)();
    void (*cmdptr)(char*);
};

typedef struct {
    char *lexema;
    int compLex;
    union Valor valor;
} componente;

extern const componente palabrasReservadas[];
extern int imprimirResultados;

#endif /* DEFINICIONES_H */