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

int main() {
	int sockfd;
	char buffer[100];
	char *hello_msg = "Hello from client";
	struct sockaddr_in servaddr;
	 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
	    err_handle("Socket creation failed");
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	int n, len;
	len = sizeof(servaddr); 
	sendto(sockfd, hello_msg, strlen(hello_msg),0, (struct sockaddr *) &servaddr, sizeof(servaddr));
	n = recvfrom(sockfd, buffer,100,0, (struct sockaddr *) &servaddr,&len);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);
	
	close(sockfd);
	return 0;
}

