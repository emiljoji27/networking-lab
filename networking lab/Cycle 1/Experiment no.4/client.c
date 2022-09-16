#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT	 8080

void err_handle(char *msg)
{
  printf("%s\n",msg);
  exit(-1);
}	

void main() 
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char buff[100];

	servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    
    int n;
    printf("Enter the no.of elements : ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements : ");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    write(sockfd,&n,sizeof(int));
    write(sockfd,arr,n*sizeof(int));
    read(sockfd,&n,sizeof(int));
    printf("Average = %d\n",n);
    close(sockfd);
}

