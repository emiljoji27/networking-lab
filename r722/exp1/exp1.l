identifier [a-zA-Z][a-zA-Z0-9]*

%%

#.* {printf("\n%s is a preprocessor directive",yytext);}

int |
float |
char |
double |
while |
for |
struct |
typedef |
do |
if |
break |
continue |
void |
switch |
return |
else |
goto {printf("\n%s is a KEYWORD", yytext);}

\/\/.* {printf("\n%s is a COMMENT", yytext);}

{identifier}\( {printf("\nFUNCTION\n%s", yytext);}

\{ {printf("\n"); ECHO; printf("\nBLOCK BEGINS");}

\} {printf("\nBLOCK ENDS\n"); ECHO;}

{identifier}(\[[0-9]*\])? {printf("\n%s is an IDENTIFIER", yytext);}

\".*\" {printf("\n%s is a STRING", yytext);}

[0-9]+ {printf("\n%s is a NUMBER", yytext);}

\)(\:)? {printf("\n"); ECHO; printf("\n");}

\( ECHO;

= {printf("\n%s is an ASSIGNMENT OPERATOR", yytext);}

\<= |
\>= |
\< |
== |
\> {printf("\n%s is a RELATIONAL OPERATOR", yytext);}

\+ |
\- |
\* |
\/ |
\^ {printf("\n%s is a ARITHMETIC OPERATOR", yytext);}

%%

int main() 
{
  char filename[50];
	
  printf("Enter filename: ");  
  scanf("%s", filename);
	
  FILE *file;
  file = fopen(filename,"r");
	
  if(!file) 
   {
      printf("Could not open the file\n");
      exit(0);
   }
	
  yyin = file;
  yylex();
  printf("\n");
  return(0);
}

int yywrap() 
{
  return(1);
}
