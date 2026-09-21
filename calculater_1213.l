%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      {
                yylval = atoi(yytext);
                return NUMBER;
            }

[ \t]+      ;

\n          { return '\n'; }

.           { return yytext[0]; }

%%
 
int yywrap()
{
    return 1;
}

calculater_1213.y
  %{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

%token NUMBER

%%

lines:
      /* empty */
    | lines line
    ;

line:
      '\n'
    | exp '\n'       { printf("Result = %d\n", $1); }
    | error '\n'     { 
                        printf("Syntax Error! Please re-enter.\n");
                        yyerrok;
                      }
    ;

exp:
      exp '+' exp    { $$ = $1 + $3; }
    | exp '-' exp    { $$ = $1 - $3; }
    | exp '*' exp    { $$ = $1 * $3; }
    | exp '/' exp    {
                        if ($3 == 0) {
                            printf("Error: Division by zero\n");
                            $$ = 0;
                        }
                        else
                            $$ = $1 / $3;
                      }
    | '(' exp ')'    { $$ = $2; }
    | NUMBER         { $$ = $1; }
    ;

%%

void yyerror(char *s)
{
    /* Error is handled in the grammar using error token */
}

int main()
{
    printf("Desk Calculator\n");
    printf("Enter expressions (Ctrl+C to exit):\n");

    yyparse();

    return 0;
}
