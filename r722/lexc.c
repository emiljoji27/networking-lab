#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


bool isValidOperator(char ch)
{
  if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='>'||ch=='<'||ch=='=')
     return true;
  return false;
}

bool isValidKeyword(char* str) {
   if (!strcmp(str, "if")||!strcmp(str,"else")||!strcmp(str,"while")|!strcmp(str,"break")||!strcmp(str,"int")||!strcmp(str, "switch")||!strcmp(str,"void")
   ||!strcmp(str,"double")||!strcmp(str,"float")||!strcmp(str, "return")||!strcmp(str,"char")||!strcmp(str,"char")||!strcmp(str,"sizeof"))
          return (true);
   return (false);
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
        printf("	<==This is a line!!\n");
  }
  fclose(fp);
}


