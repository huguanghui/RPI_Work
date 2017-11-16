%{
#include <stdio.h>
%}
%%
[a-zA-Z]+ {printf("Get Word:%s\n", yytext);}
[0-9]+ {printf("Get Num:%s\n", yytext);}
\n     {printf("New Line\n");}
.      {}
%%
