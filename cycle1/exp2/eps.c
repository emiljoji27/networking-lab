#include<stdio.h>
#include<stdlib.h>


struct flag
{
 int mat[100];
 int flag[100][100];
};

struct flag state[100];
int arr[10][10];

void findClosure(int curr,int a,int b,int n)
{
 for(int i=a;i<n;i++)
  {
    for(int j=b;j<n;j++)
    {
      if(state[curr].flag[i][j]==1)
          return;
         
      state[curr].flag[i][j]=1;

      if(arr[i][j]==2)
      {
         printf("i=%d j=%d curr=%d\n",i,j,curr);
         state[curr].mat[j]=1;
         findClosure(curr,j,0,n);
      }
      else
         state[curr].mat[j]=-1;
    }
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
  for(int curr=0;curr<n;curr++)
  {
     findClosure(curr,0,0,n);
     state[curr].mat[curr]=1;
  }


  for(int i = 0; i < n; i++){
		k = 0;
		
		temp=i;//strcpy(temp, states[i]);
		k = add_state(states[i], k);
		
		for(int p = 0; p < k; p++) {			
			strcpy(state, result[p]);

			for(int j = 0; j < m; j++){
				if(!strcmp(state, table[j].state1)){
					if(!strcmp(table[j].input, "e")) {
						k = add_state(table[j].state2, k);
					}
				}
			}
		}
		
		display(k);
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

