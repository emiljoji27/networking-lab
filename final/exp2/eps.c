#include<stdio.h>
#include<stdlib.h>


struct flag
{
 int mat[100];
};

struct flag state[100];
int arr[10][10];

void findClosure(int curr,int a,int b,int n)
{
 for(int i=a;i<n;i++)
  {
    for(int j=b;j<n;j++)
    {
      if(i==j)
          continue;

      if(j==curr)
          continue;

      if(state[curr].mat[j]==2)
          continue;

      if(state[curr].mat[i]!=1 && state[curr].mat[i]!=2)
          continue;

      if(arr[i][j]==2)
      {
         //printf("i=%d j=%d curr=%d\n",i,j,curr);
         state[curr].mat[j]=2;
         findClosure(curr,j,0,n);
      }
      else
         state[curr].mat[j]=-1;
    }
    b=0;
  }
}


void main()
{
  int n;
  printf("Enter the number of states : ");
  scanf("%d",&n);
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
      {
         state[i].mat[j]=1;
      }
    }
    state[i].mat[i]=1;
  }

  for(int curr=0;curr<n;curr++)
  {
     findClosure(curr,curr,0,n);
     state[curr].mat[curr]=2;
  }

  for(i=0;i<n;i++)
  {
    printf("Epsilon-closure of q[%d] : ",i);
    for(j=0;j<n;j++)
    {
      if(state[i].mat[j]==1 || state[i].mat[j]==2)
         printf("q[%d] ",j);
    }
    printf("\n");
  }
  
}

