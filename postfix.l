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

postfix.y
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
    | exp '\n'    { printf("Result = %d\n", $1); }
    ;

exp:
      exp '+' exp  { $$ = $1 + $3; }
    | exp '-' exp  { $$ = $1 - $3; }
    | exp '*' exp  { $$ = $1 * $3; }
    | exp '/' exp  {
                      if ($3 == 0)
                          printf("Error: Division by zero\n");
                      else
                          $$ = $1 / $3;
                    }
    | NUMBER       { $$ = $1; }
    ;

%%

void yyerror(char *s)
{
    printf("Syntax Error!\n");
}

int main()
{
    printf("Enter expression:\n");
    yyparse();
    return 0;
}
