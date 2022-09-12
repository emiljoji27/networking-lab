#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>
#include<limits.h>

int smallest_not_visited(int dist_vect[],int visited[], int t,int n)
{
    int smallest_dist = INT_MAX;
    int pos = -1;
    for(int i = 0; i<n; i++){
        if(visited[i] != 1 && dist_vect[i] < smallest_dist){
            smallest_dist = dist_vect[i];
            pos = i;
        }
    }
    return pos;
}

void main()
{
    printf("Enter number of nodes:");
    int n;
    scanf("%d",&n);
    int arr[n][n];

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&arr[i][j]);
        }
    }
    
    for(int i=0; i<n; i++){
        int src = i;
        int dist_vect[50];
        int visited [50] = {0};
        int solution [50] = {-1};
        //initialize the distance vector
        printf("---------------------------\n");
        for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",arr[i][j]);
          }
         printf("\n");
        }

        printf("Initial Distance Vector: ");
        for(int i=0;i<n;i++){
            dist_vect[i] = arr[src][i] == -1 ? INT_MAX : arr[src][i];
            printf("%d(%d) ",arr[src][i],dist_vect[i]);
        }
        solution[0] = src;
        visited[src] = 1;
        printf("\n");
        for(int i=0; i<n-1;i++){
           int j = smallest_not_visited(dist_vect,visited,i,n);
           visited[j] = 1;
           printf("Distance vector on %d: ",j);
           for(int i=0; i<n;i++) 
               printf("%d ",dist_vect[i]);
           printf("\n");
           for(int k = 0; k<n; k++){
               if(visited[k]!=1) {
                   int sum = (arr[j][k] == -1) ? INT_MAX : dist_vect[j]+arr[j][k];
                   if(dist_vect[k] > sum ){
                       dist_vect[k] = dist_vect[j]+arr[j][k];
                   }
               }
            }
            solution[i+1] = j;
        }
        printf("Dijistra on point %d : ",src);
        for(int i=0;i<n;i++){ 
            printf("%d (%d) ",solution[i],dist_vect[solution[i]]);
        }
        printf("\n");
        printf("\n");
    }
}
