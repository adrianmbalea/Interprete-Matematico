#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#define VAR 300
#define CONST 301
#define CMD 302
#define COMENTARIO 303

typedef struct {
    char *lexema;
    int compLex;
    union {
        double var;
        double (*funcptr)();
    } valor;
} componente;

static const componente palabrasReservadas[] = {
    {"echo", CMD, .valor.var=echo},
    {"quit", CMD, .valor.var=quit},
    {"workspace", CMD, .valor.var=workspace},
    {"clear", CMD, .valor.var=clear},
    {"help", CMD, .valor.var=help},
    {"load", CMD, .valor.var=load},
    {"pi", CONST, 3.141592653589},
    {"e", CONST, 2.718281828459},
};

int imprimirResultados=1;

#endif	/* DEFINICIONES_H */

