#ifndef LEX_YY_H
#define LEX_YY_H

#include "definiciones.h"

void abrirArchivo(char *nombreArchivo);
void cerrarArchivo();
void liberarLexico();

extern int script;
extern FILE* yyin;

#endif /*LEX_YY_H*/