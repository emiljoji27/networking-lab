#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


bool isValidOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '|' || ch == '&' || ch == '!')
		return true;
    	
	return false;
}

bool isValidKeyword(char* str) {
    if (!strcmp(str, "auto") || !strcmp(str, "default") || !strcmp(str, "signed") || !strcmp(str, "enum") ||!strcmp(str, "extern") || !strcmp(str, "for") || !strcmp(str, "register") || !strcmp(str, "if") || !strcmp(str, "else")  || !strcmp(str, "int")|| !strcmp(str, "while") || !strcmp(str, "do")|| !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "double") || !strcmp(str, "float")|| !strcmp(str, "return") || !strcmp(str, "char")|| !strcmp(str, "case") || !strcmp(str, "const")|| !strcmp(str, "sizeof") || !strcmp(str, "long")|| !strcmp(str, "short") || !strcmp(str, "typedef")|| !strcmp(str, "switch") || !strcmp(str, "unsigned")|| !strcmp(str, "void") || !strcmp(str, "static")|| !strcmp(str, "struct") || !strcmp(str, "goto")|| !strcmp(str, "union") || !strcmp(str, "volatile"))
        return true;
    return false;
}

bool isValidInteger(char* str)
{
  char buffer[20];
  sprintf(buffer,"%d",atoi(str));
  if(strlen(str)==strlen(buffer))
    return true;
  return false;
}

bool isValidDelimiter(char ch)
{
  if(ch==' '||ch==';'||ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'||ch=='\n'||ch=='"'||ch==',')
     return true;
  return false;
}

void detectTokens(char* str)
{
   int left = 0, right = 0;
   int length = strlen(str);
   while (right<=length&&left<=right)
   {
      if (isValidDelimiter(str[right])==false)
          right++;
      if (isValidDelimiter(str[right])==true&&left==right)
      {
         if (isValidOperator(str[right])==true)
         printf("Valid operator : '%c'\n",str[right]);
         right++;
         left = right;
      }
      else if (isValidDelimiter(str[right]) == true && left!=right||(right==length&&left!=right))
      {
         char* subStr = subString(str, left, right - 1);
         if (isValidKeyword(subStr) == true)
            printf("Valid keyword : '%s'\n", subStr);
         else if (isValidInteger(subStr) == true)
            printf("Valid Integer : '%s'\n", subStr);
         else if (isRealNumber(subStr) == true)
            printf("Real Number : '%s'\n", subStr);
         else if (isvalidIdentifier(subStr) == true && isValidDelimiter(str[right - 1]) == false)
            printf("Valid Identifier : '%s'\n", subStr);
         else if (isvalidIdentifier(subStr) == false && isValidDelimiter(str[right - 1]) == false)
            printf("Invalid Identifier : '%s'\n", subStr);
         left = right;
      }
   }
}

void main()
{
  FILE* fp;
  fp=fopen("lexc.c","r");
  char str[1000];
  while (fgets(str,1000,fp) != NULL)
  {    
        int i=0;
        while(str[i]!='\n')
        {
         printf("%c", str[i]);
         i++;
        }
        printf(" <==This is a line!!\n");
  }
  fclose(fp);
}




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int isKeyword(char* str)
{
    if (!strcmp(str, "auto") || !strcmp(str, "default") || !strcmp(str, "signed") || !strcmp(str, "enum") ||!strcmp(str, "extern") || !strcmp(str, "for") || !strcmp(str, "register") || !strcmp(str, "if") || !strcmp(str, "else")  || !strcmp(str, "int")|| !strcmp(str, "while") || !strcmp(str, "do")|| !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "double") || !strcmp(str, "float")|| !strcmp(str, "return") || !strcmp(str, "char")|| !strcmp(str, "case") || !strcmp(str, "const")|| !strcmp(str, "sizeof") || !strcmp(str, "long")|| !strcmp(str, "short") || !strcmp(str, "typedef")|| !strcmp(str, "switch") || !strcmp(str, "unsigned")|| !strcmp(str, "void") || !strcmp(str, "static")|| !strcmp(str, "struct") || !strcmp(str, "goto")|| !strcmp(str, "union") || !strcmp(str, "volatile"))
        return 1;
    return 0;
}
int isFunction(char *str)
{
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]=='(')
		{
			return 1;
		}
	}
	return 0;
}
int hasComma(char *str)
{
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]==',')
		{
			return 1;
		}
	}
	return 0;
}
int hasEqualto(char *str)
{
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]=='=')
		{
			return 1;
		}
	}
	return 0;
}
void main()
{
	char filename[20],data[1024];
	printf("Enter the input filename : ");
	int multilinecomment=0;
	scanf("%s",filename);
	printf("\n");
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("No such file exists\n");
	}
	else
	{
		while(fgets(data,1024,fp)!=NULL)
		{
			int length=strlen(data);
			if(data[0] == '/' && data[1]=='/')
			{
				printf("%s is a comment\n\n",data);
			}
			else if(multilinecomment ==1 || ( data[0]=='/' && data[1]=='*'))
			{
				multilinecomment=1;
				printf("%s is a multi line comment\n\n");
				if(data[strlen(data)-1]=='*' && data[strlen(data)-2]=='/')
					multilinecomment=0;
				
			}
			
			else if(data[0]=='#')
			{
				printf("%sis a preprocessor directive\n\n",data);
			}
			else if(data[0]=='p' && data[1]=='r' && data[2]=='i' && data[3]=='n' &&data[4]=='t'&&data[5]=='f')
			{
				printf("printf is a function\n\n");
				int start=0;
				for (int i=0;i<strlen(data);i++)
				{
					
					if(data[i]=='"' && start==0)
					{
						start=1;
						continue;
					}
					else if(data[i]=='"' && start==1)
						start=2;
					if (start==1)
					{
						printf("%c",data[i]);
					}
					else if(start==2)
					{
						printf(" is a literal \n\n");
						break;
					}
					
						
				}
			}
			else if(data[0]=='s' && data[1]=='c' && data[2]=='a' && data[3]=='n' && data[4]=='f')
			{
				printf("scanf is a function\n\n");
				int start=0;
				for (int i=0;i<strlen(data);i++)
				{
					
					if(data[i]=='"' && start==0)
					{
						start=1;
						continue;
					}
					else if(data[i]=='"' && start==1)
						start=2;
					if (start==1)
					{
						printf("%c",data[i]);
					}
					else if(start==2)
					{
						printf(" is a literal \n\n");
					}
					
						
				}
			}
			else
			{
				char* token;
				token=strtok(data, " ");
				while( token != NULL ) {
					if(isKeyword(token))
					{
						printf("%s is a valid keyword\n\n",token);
					}
					
					else if(isFunction(token))
					{
						printf("%s is a function\n\n",token);
					}
					else
					{
						if(hasComma(token))
						{
							char * subtoken;
							subtoken=strtok(data,",");
							printf("%s is an identifier\n\n");
							printf(", is a delimiter\n\n");
							while(subtoken!=NULL)
							{
								printf("%s is an identifier\n\n");
								subtoken=strtok(NULL,",");
							}
						}
						else if(hasEqualto(token))
						{
							char * subtoken;
							subtoken=strtok(data,"=");
							printf("%s is an identifier\n\n");
							printf("= is an assignment operator\n\n");
							while(subtoken!=NULL)
							{
								if(isdigit(subtoken[0]))
								{
									printf("%s is a number\n\n");
								}
								else if(isalpha(subtoken[0]))
								{
									printf("%s is a character string\n\n");
								}
								subtoken=strtok(NULL,"=");
							}
							
						}
						else if(isdigit(data[0]))
						{
							printf("%s is number\n\n");	
						}
						
					}
					
					token=strtok(NULL, " ");
		   		}
		   			
			}
			if(data[length-2]==';')
			{
				printf("; is a delimiter\n\n");
			}
			
		}
	}
	
}
