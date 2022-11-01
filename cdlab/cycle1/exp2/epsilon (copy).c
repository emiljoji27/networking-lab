#include<stdio.h>
#include<stdlib.h>
void main()
{
	char filename[20],data[1024];
	int n;
	printf("Enter the number of states : ");
	scanf("%d",&n);
	int mat[n][n-1];
	printf("Enter the input filename : ");
	scanf("%s",filename);
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("No such file exists\n");
	}
	else
	{
		while(fgets(data,1024,fp)!=NULL)
		{
			char *token;
			char states[3];
			int i=0;
			token=strtok(data," ");
			while(token!=NULL)
			{
				states[i]=token;
				token=strtok(NULL," ");
				i++;
			}
			int j=0,k=0;
			while(j<1)
			{
				if(states[1]=='e')
				{
					mat[states[0]-'0'][k]=states[2]-'0';
					k++;
				}
			}
		}
		int m=0,p=0;
		while(m<n)
		{
			printf("Epsilon closure of state %d is - ",m);
			while(1)
			{
				printf("%d ",mat[m][p]);
				
			}
		}
	}
	
}

}
