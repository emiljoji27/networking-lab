#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isFunction = false;
bool isComment = false;

bool isDelimiter(char ch) 
{
	if (ch == ' ' || ch == '\t' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!' || ch == '|' || ch == '&' || ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\'' || ch == '\"') 
	  return true;

	return false;
}

bool isOperator(char ch) 
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '|' || ch == '&' || ch == '!')
		return true;
    	
	return false;
}

bool separatorCheck(char* str) 
{
	if(!strcmp(str, "(")) 
	   printf("(\n");
	else if(!strcmp(str, ")")) 
	{ 
	   isFunction = false; 
	   printf(")\n"); 
	}
	else if(!strcmp(str, "{")) 
	   printf("Block begins\n{\n");
	else if(!strcmp(str, "}")) 
	   printf("Block ends\n}\n");
	else if(!strcmp(str, ",")) 
	   printf(", is a separator\n");
	else if(!strcmp(str, ";")) 
	   printf("; is a delimiter\n");
	else return false;
	
	return true;
}

bool operatorCheck(char* str) 
{
	if(!strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "*") || !strcmp(str, "/"))
		printf("%s is an arithmetic operator\n", str);
	else if(!strcmp(str, "="))
		printf("%s is an assignment operator\n", str);
	else if(!strcmp(str, "<") || !strcmp(str, ">") || !strcmp(str, "<=") || !strcmp(str, ">=") || !strcmp(str, "==") || !strcmp(str, "!="))
		printf("%s is a relational operator\n", str);
	else if(!strcmp(str, "!") || !strcmp(str, "||") || !strcmp(str, "&&"))
		printf("%s is a logical operator\n", str);
	else if(!strcmp(str, "|") || !strcmp(str, "&"))
		printf("%s is a bitwise operator\n", str);
	else if(!strcmp(str, "++") || !strcmp(str, "--") || !strcmp(str, "+=") || !strcmp(str, "-=") || !strcmp(str, "*=") || !strcmp(str, "/=") || !strcmp(str, "|=") || !strcmp(str, "&="))
		printf("%s is a compound operator\n", str);
	else if(!strcmp(str, "["))
		printf("[ is array index operator begin\n");
	else if(!strcmp(str, "]"))
		printf("] is array index operator end\n");
	else return false;
	
	return true;
}

bool keywordCheck(char* str) 
{
	if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "for") || !strcmp(str, "do") || !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "char") || !strcmp(str, "bool") || !strcmp(str, "true") || !strcmp(str, "false") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto")) {
		printf("%s is a keyword\n", str);
		return true;
	}
	
	return false;
}

bool integerCheck(char* str) 
{
	int i, len = strlen(str);
	
	if(len == 0)
		return false;
	for(i = 0; i < len; i++)
	 {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
			return false;
    	}
	
	printf("%s is an integer\n", str);
	return true;
}

bool realNumberCheck(char* str) 
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if(len == 0)
		return false;
	for(i = 0; i < len; i++) 
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
		    return false;
		if (str[i] == '.')
			hasDecimal = true;
	}
	
	if(hasDecimal) printf("%s is a real number\n", str);
	
	return hasDecimal;
}

bool charCheck(char* str) 
{
	if(str[0] == '\'' && str[strlen(str) - 1] == '\'')
	 {
		printf("%s is a character\n", str);
		return true;
	}
	
	return false;
}

bool strCheck(char* str) 
{
	if(str[0] == '\"' && str[strlen(str) - 1] == '\"') 
	{
		printf("%s is a string\n", str);
		return true;
	}
	
	return false;
}

bool identifierCheck(char* str) 
{ 
	if(str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9' || isDelimiter(str[0]) == true) 
		return false;
	
	return true;
}

char* substr(char* str, int start, int end)
{
	char* sub = malloc(sizeof(char) * (end - start + 2));
	
	int i;
	
	for(i = 0; i < (end - start + 1); i++) 
		sub[i] = str[start + i];
	
	sub[i] = '\0';
	return sub;
}

bool preprocessorCheck(char str[]) 
{
	int i = 0;
	while(str[i] == ' ') i++;
        if(str[i] == '#') 
        {
		printf("%s is a preprocessor directive\n", str);
		return true;
	}
	return false;
}

void parse(char str[]) 
{
        int flag=-1;
	if(preprocessorCheck(str) || !strcmp(str, "\n")) return;
	
	int start = 0, end = 0, len = strlen(str);
	char* lexeme;
	
	while (start <= end && end < len) {
	        flag=-1;
		if(str[start] == '\'') 
		{
			end++;
			while(str[end] != '\'')
			  end++;
                       end++;
		} 
		else if(str[start] == '\"') 
		{
			end++;
			while(str[end] != '\"') 
			  end++;
			end++;
		} 
		else if(str[start] == '/' && str[start + 1] == '/') 
		{
			printf("%s is a single line comment\n", substr(str, start, strlen(str) - 1));
			end++;
			start = end;
			return;
		} 
		else if(str[start] == '/' && str[start + 1] == '*') {
			isComment = true;
			end += 2;
			while((end + 1) < len) 
			{
				if(str[end] == '*' && str[end + 1] == '/') 
				{
					end++;
					printf("%s is a multiline comment\n", substr(str, start, end));
					isComment = false;
					break;
				}
				else
					end++;
			}
			if(isComment) 
			{ 
			  printf("%s is a multiline comment\n", substr(str, start, len - 1)); 
                         return; 
                       }
			end++;
			start = end;
		} 
		else if(str[start] == '*' && str[start + 1] == '/') 
		{
			isComment = false;
			printf("%s is a multiline comment\n", substr(str, 0, start + 1));
			start += 2;
			end = start;
		}
		
		
		if(!isDelimiter(str[end])) 
		{
			end++;
			if(end == len)
			   flag=0;
		} 
		else
		  flag=0;
		if(flag==0)
		{
			if(start == end) 
			{
				if(isOperator(str[end]) && end + 1 < len && isOperator(str[end + 1]))
					end++;
			} 
			else {
				end--;
			}		
			
			lexeme = substr(str, start, end);
			
			if(isComment) {
				
			} 
			else if(operatorCheck(lexeme)) {
				
			} 
			else if(separatorCheck(lexeme)) {
				
			} 
			else if(keywordCheck(lexeme)) {
				
			} 
			else if(integerCheck(lexeme)) {
				
			} 
			else if(realNumberCheck(lexeme)) {
				
			} 
			else if(charCheck(lexeme)) {
				
			} 
			else if(strCheck(lexeme)) {
				
			} 
			else if(identifierCheck(lexeme))
			{
				if(end + 1 < len && str[end + 1] == '(') {
					printf("%s is a function\n", lexeme);
					isFunction = true;
				}
				else if(isFunction) {
					printf("%s is an argument\n", lexeme);
				} else {
					printf("%s is an identifier\n", lexeme);
				}
			} 
			else if(strcmp(lexeme, " ") && strcmp(lexeme, "\t") && strcmp(lexeme, "\n"))
				printf("%s is an invalid token\n", lexeme);
			
			end++;
			start = end;
		}
	}
		
	if(isComment) {
		printf("%s is a multiline comment\n", str);
	}
}

void main() 
{
	char filename[20];
	printf("Enter input filename: ");
	scanf("%s", filename);
	
	FILE *fp = fopen(filename, "r");
	
	char str[1000];
	
	while(fgets(str, 1000, fp)) 
	{
		str[strlen(str) - 1] = '\0';
		parse(str);
	}
}

/* Lexical
analyser
is
done */
