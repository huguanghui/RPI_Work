%{
#include "stdio.h"
int linenum;
%}
int [0-9]+
float [0-9]*\.[0-9]+
%%
[\n]                    linenum ++;
title                 showtitle();
{int}                 printf("Int :%s\n", yytext);
{float}                 printf("Float :%s\n", yytext);
.                     printf("Unknown :%d %c\n", linenum, yytext[0]);
%%
showtitle()
{
printf("----- Lex Example -----\n");
}

int main()
{
  linenum=0;
  yylex(); /* 进行分析 */
  printf("\nLine Count: %d\n",linenum);
  return 0;
}
int yywrap()
{
return 1;
}