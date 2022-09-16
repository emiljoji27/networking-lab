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
    write(connfd,buff,sizeof(buff));
    bzero(buff,sizeof(buff));
    read(connfd,buff,sizeof(buff));
    puts(buff);
    close(sockfd);
}

