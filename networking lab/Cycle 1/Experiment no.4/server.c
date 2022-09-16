#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
	
void err_handle(char *msg)
{
  printf("%s\n",msg);
  exit(-1);
}

void main() 
{
	int sockfd,connfd;
    struct sockaddr_in servaddr,cli;
    char buff[100];
    printf("Enter the message to client : ");
    fgets(buff,100,stdin);
    printf("Why??????\n");
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sockfd,1);
    int len=sizeof(cli);
    connfd=accept(sockfd,(struct sockaddr*)&cli,&len);
    int n;
    read(connfd,&n,sizeof(int));
    int arr[n];
    read(connfd,arr,n*sizeof(int));
    int avg=0;
    for(int i=0;i<n;i++)
       avg+=arr[i];
    avg/=n;
    write(connfd,&avg,sizeof(int));
    close(sockfd);
}

