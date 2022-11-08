#include<stdio.h>
#include<stdlib.h>


struct flag
{
 int mat[100];
};

void main()
{
  int n;
  printf("Enter the number of states : ");
  scanf("%d",&n);
  struct flag state[n];
  int arr[n][n];
  int i=0,j=0;
  printf("\n0:no transition || 1:non-epsilon transition || 2:epsilon transition\n\n");
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
     printf("q[%d] and q[%d] : ",i,j);
     scanf("%d",&arr[i][j]);
    }
  }
  
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      if(arr[i][j]==2)
         state[i].mat[j]=1;
      else
         state[i].mat[j]=-1;
    }
    state[i].mat[i]=1;
  }

  int curr=0;
  while(curr<n)
  {
    i=curr;
    j=0;
    while(j<n)
    {
     if(j==i)
      j++;
 
     if(i<curr)
       break;

     if(state[i].mat[j]==1)
      {
        state[curr].mat[j]=1;   
        i=j;
        j=0;
        continue;
      }
     j++;
    }
    curr++;
  }
  
  for(i=0;i<n;i++)
  {
    printf("Epsilon-closure of q[%d] : ",i);
    for(j=0;j<n;j++)
    {
      if(state[i].mat[j]==1)
         printf("q[%d] ",j);
    }
    printf("\n");
  }
  
}

