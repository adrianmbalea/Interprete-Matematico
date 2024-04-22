%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "../includes/definiciones.h"
    #include "../includes/lex.yy.h"
    #include "../includes/ts.h"
    #include "../includes/errores.h"

    void yyerror(char *s);
    extern int yylex();

    int error = 0;
%}

%union {
    double      numero;
    char*       cadena; 
}

%token  <numero>    NUM
%token  <cadena>    VAR FUNC CONST
%token  <numero>    MENOR_IGUAL MAYOR_IGUAL IGUAL_IGUAL DISTINTO MAS_IGUAL MENOS_IGUAL POR_IGUAL SLASH_IGUAL PORCENTAJE_IGUAL
%type   <numero>    exp

%left MENOR_IGUAL MAYOR_IGUAL IGUAL_IGUAL DISTINTO
%left '+'
%left '-'
%left '*'
%left '/'
%left '%'
%right '^'
%right '='
%right MAS_IGUAL MENOS_IGUAL POR_IGUAL SLASH_IGUAL PORCENTAJE_IGUAL
%left NEG

%start input

%%

input: %empty   { printf(">>> "); }
| input line
;

line:
'\n'                    {   printf(">>> "); error = 0;}
| exp '\n'              { 
                            if(!error){
                                if(!isnan($1)){
                                    printf("%g\n\n", $1);
                                } else {
                                    imprimirError(NAN_DETECTADO);
                                }
                            } else {
                                imprimirError(error);
                            }
                            printf(">>> ");
                            error = 0;
                        }
| exp ';' '\n'          { 
                            if(!error){
                                if(!isnan($1)){
                                    printf("%g\n\n", $1);
                                } else {
                                    imprimirError(NAN_DETECTADO);
                                }
                            } else {
                                imprimirError(error);
                            }
                            printf(">>> ");
                            error = 0;
                        }

| asignacion '\n'       { 
                            if(error) imprimirError(error);
                            printf(">>> ");
                            error = 0;
                        }
| asignacion ';' '\n'   { 
                            if(error) imprimirError(error);
                            printf(">>> ");
                            error = 0;
                        }

| comparacion '\n'      { 
                            if(error) imprimirError(error);
                            printf(">>> ");
                            error = 0;
                        }
| comparacion ';' '\n'  { 
                            if(error) imprimirError(error);
                            printf(">>> ");
                            error = 0;
                        }

| error '\n'            {   yyerrok; error = 0; printf(">>> "); }
;



exp: 
NUM                         { $$ = $1; }

| CONST                     {   componente c = buscarComponente($1);
                                if(c.lexema!=NULL) { $$=c.valor.var; }
                                else { error = VARIABLE_NO_DEFINIDA; $$ = NAN; }
                            }

| VAR                       {   componente c = buscarComponente($1);
                                if(c.lexema!=NULL) { $$=c.valor.var; }
                                else { error = VARIABLE_NO_DEFINIDA; $$ = NAN; }
                            }

| FUNC '(' ')'              {   componente c = buscarComponente($1);
                                if(c.compLex==FUNC) { double result = (*(c.valor.funcptr))(); $$ = result; if(isnan(result)) { error = PARAMETROS_INCORRECTOS_FUNC; } }
                                else  { error = SYNTAX_ERROR; }
                            }

| FUNC '(' exp ')'          {   componente c = buscarComponente($1);
                                if(c.compLex==FUNC) { double result = (*(c.valor.funcptr))($3); $$ = result; if(isnan(result)) { error = PARAMETROS_INCORRECTOS_FUNC; } }
                                else  { error = SYNTAX_ERROR; }
                            }

| FUNC '(' exp ',' exp ')'  {   componente c = buscarComponente($1);
                                if(c.compLex==FUNC) { double result = (*(c.valor.funcptr))($3, $5); $$ = result; if(isnan(result)) { error = PARAMETROS_INCORRECTOS_FUNC; } }
                                else  { error = SYNTAX_ERROR; }
                            }

| exp '+' exp               { $$ = $1 + $3; }
| exp '-' exp               { $$ = $1 - $3; }
| exp '*' exp               { $$ = $1 * $3; }
| exp '/' exp               { $$ = $1 / $3; }
| '-' exp %prec NEG         { $$ = -$2; }
| exp '^' exp               { $$ = pow($1, $3); }
| exp '%' exp               { $$ = (int)$1%(int)$3; }
| '(' exp ')'               { $$ = $2; }
;



asignacion:
VAR '=' exp                 {   componente c = buscarComponente($1);
                                if(c.compLex!=VAR && c.compLex!=-2) error=ASIGNACION_NO_VARIABLE;
                                else if(!isnan($3)) insertarLex($1, VAR, (union Valor)$3);
                                else error = NAN_DETECTADO;
                            }

| VAR MAS_IGUAL exp         {   componente c = buscarComponente($1);
                                if(c.compLex!=VAR && c.compLex!=-2) error=ASIGNACION_NO_VARIABLE;
                                else if(!isnan($3)) insertarLex($1, VAR, (union Valor)(c.valor.var+$3));
                                else error = NAN_DETECTADO;
                            }

| VAR MENOS_IGUAL exp       {   componente c = buscarComponente($1);
                                if(c.compLex!=VAR && c.compLex!=-2) error=ASIGNACION_NO_VARIABLE;
                                else if(!isnan($3)) insertarLex($1, VAR, (union Valor)(c.valor.var-$3));
                                else error = NAN_DETECTADO;
                            }

| VAR POR_IGUAL exp         {   componente c = buscarComponente($1);
                                if(c.compLex!=VAR && c.compLex!=-2) error=ASIGNACION_NO_VARIABLE;
                                else if(!isnan($3)) insertarLex($1, VAR, (union Valor)(c.valor.var*$3));
                                else error = NAN_DETECTADO;
                            }

| VAR SLASH_IGUAL exp       {   componente c = buscarComponente($1);
                                if(c.compLex!=VAR && c.compLex!=-2) error=ASIGNACION_NO_VARIABLE;
                                else if(!isnan($3)) insertarLex($1, VAR, (union Valor)(c.valor.var/$3));
                                else error = NAN_DETECTADO;
                            }

| VAR PORCENTAJE_IGUAL exp  {   componente c = buscarComponente($1);
                                if(c.compLex!=VAR && c.compLex!=-2) error=ASIGNACION_NO_VARIABLE;
                                else if(!isnan($3)) insertarLex($1, VAR, (union Valor)(double)((int)c.valor.var%(int)$3));
                                else error = NAN_DETECTADO;
                            }
;


comparacion:
exp IGUAL_IGUAL exp         {   
                                if(isnan($1) || isnan($3)) error = NAN_DETECTADO;
                                else { if($1==$3)printf("True\n\n"); else printf("False\n\n");} 
                            }

| exp '>' exp       {   
                                if(isnan($1) || isnan($3)) error = NAN_DETECTADO;
                                else { if($1>$3)printf("True\n\n"); else printf("False\n\n");} 
                            }

| exp '<' exp       {   
                                if(isnan($1) || isnan($3)) error = NAN_DETECTADO;
                                else { if($1<$3)printf("True\n\n"); else printf("False\n\n");} 
                            }

| exp MENOR_IGUAL exp       {   
                                if(isnan($1) || isnan($3)) error = NAN_DETECTADO;
                                else { if($1<=$3)printf("True\n\n"); else printf("False\n\n");} 
                            }

| exp MAYOR_IGUAL exp       {   
                                if(isnan($1) || isnan($3)) error = NAN_DETECTADO;
                                else { if($1>=$3)printf("True\n\n"); else printf("False\n\n");} 
                            }

| exp DISTINTO exp       {   
                                if(isnan($1) || isnan($3)) error = NAN_DETECTADO;
                                else { if($1!=$3)printf("True\n\n"); else printf("False\n\n");} 
                            }
;


%%

void yyerror (char *s) 
{
    imprimirError(SYNTAX_ERROR);
}