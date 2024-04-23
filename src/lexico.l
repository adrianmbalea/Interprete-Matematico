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
COMENTARIO #.*

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

/* String */
STRING \".*\"|\'.*\'

%%

{ID}                {
                        yylval.cadena = strdup(yytext);
                        componente comp = buscarComponente(yylval.cadena);
                        if(comp.lexema==NULL) return VAR;
                        return comp.compLex;
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

{STRING}            { yylval.cadena=strdup(yytext); return STRING; }
{COMENTARIO}        /* ignoramos los comentarios */

\n                  { return '\n'; }

[[:space:]]         /* ignoramos el resto de espacios */

.                   { imprimirError(LEXEMA_MAL_FORMADO); }

<<EOF>>             { cerrarArchivo(); return '\n'; }

%%

void abrirArchivo(char *filename){
    // Si no se pasa ningun archivo
    if(filename==NULL){
        script=0;
        yyin = stdin;
    } else{
        FILE *fp;
        fp=fopen(filename, "r");
        if(fp == NULL){
            imprimirError(ERROR_ARCHIVO);
            script=0;
            yyin = stdin;
        } else{
            script=1;
            yyin = fp;
        }
    }
}

void cerrarArchivo(){
    if (script==1 && yyin != NULL) {
        fclose(yyin);
        script=0;
        yyrestart(stdin);
        yyin = stdin;
    }
}

void liberarLexico(){
    if (yyin != NULL) {
        yyin = NULL;
    }
    yylex_destroy(); 
}
