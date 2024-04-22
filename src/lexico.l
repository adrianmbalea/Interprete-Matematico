%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../includes/ts.h"
#include "../includes/errores.h"
#include "../includes/lex.yy.h"
#include "../includes/sintactico.tab.h"

%}

%option noyywrap noinput nounput

/*Identificadores*/
ID [a-zA-Z_]([a-zA-Z0-9_])*

/*Numeros enteros*/
NUMERO_DECIMAL ([1-9][_0-9]*)|(0+(_?0)*)
NUMERO_HEXADECIMAL 0[xX](_?[[:xdigit:]])+
NUMERO_ENTERO ({NUMERO_DECIMAL}|{NUMERO_HEXADECIMAL})

/*Numeros flotantes*/
PARTE_DIGITOS [0-9](_?[0-9])*
PUNTO_FLOTANTE ({PARTE_DIGITOS}?\.{PARTE_DIGITOS})|({PARTE_DIGITOS}\.)
EXPONENCIAL ({PARTE_DIGITOS}|{PUNTO_FLOTANTE})[eE][\+-]?{PARTE_DIGITOS}
NUMERO_FLOTANTE ({PUNTO_FLOTANTE}|{EXPONENCIAL})

/*Comentarios*/
COMENTARIO \/\/.*|\/\*.*\*\/

/* Operadores */
OPERADOR_SIMPLE \+|-|\*|\/|%|\^|\<|\>|\(|\)|,|\.|;|=
MENOR_IGUAL \<=
MAYOR_IGUAL \>=
IGUAL_IGUAL ==
DISTINTO !=
MAS_IGUAL \+= 
MENOS_IGUAL -=
POR_IGUAL \*=
SLASH_IGUAL \/=
PORCENTAJE_IGUAL %=

%%

{ID}                {
                        yylval.cadena = strdup(yytext);
                        componente comp = buscarComponente(yylval.cadena);
                        if(comp.lexema==NULL) return VAR;
                        else return comp.compLex;
                    }

{NUMERO_ENTERO}     { yylval.numero = atof(yytext); return NUM; }
{NUMERO_FLOTANTE}   { yylval.numero = atof(yytext); return NUM; }

{OPERADOR_SIMPLE}   { return *yytext; }
{MENOR_IGUAL}       { return MENOR_IGUAL; }
{MAYOR_IGUAL}       { return MAYOR_IGUAL; }
{IGUAL_IGUAL}       { return IGUAL_IGUAL; }
{DISTINTO}          { return DISTINTO; }
{MAS_IGUAL}         { return MAS_IGUAL; }
{MENOS_IGUAL}       { return MENOS_IGUAL; }
{POR_IGUAL}         { return POR_IGUAL; }
{SLASH_IGUAL}       { return SLASH_IGUAL; }
{PORCENTAJE_IGUAL}  { return PORCENTAJE_IGUAL; }


{COMENTARIO}        /* ignoramos los comentarios */

\n                  { return '\n'; }

[[:space:]]         /* ignoramos el resto de espacios */

.                   { imprimirError(LEXEMA_MAL_FORMADO); }

<<EOF>> { yyterminate(); }

%%

int fichero=0;

void abrirArchivo(char *filename){
    // Si no se ejecuta ningun archivo
    if(filename==NULL){
        yyin = stdin;
    } else{
        FILE *fp;
        fp=fopen(filename, "r");
        if(fp == NULL){
            imprimirError(ERROR_ARCHIVO);
            yyin = stdin;
        } else{
            yyin = fp;
            fichero = 1;
        }
    }
}

void cerrarArchivo(){
    if (fichero==1 && yyin != NULL) {
        fclose(yyin);
        yyin = NULL;
    }
    yylex_destroy(); 
}
