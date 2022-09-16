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

int main() {
	int sockfd;
	char buffer[100];
	char *hello_msg = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
		
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(sockfd<0)
	    err_handle("Socket creation failed");
		
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	if (bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
	      err_handle("Bind failed");
		
	int len, n;
	len = sizeof(cliaddr); 
	n = recvfrom(sockfd, buffer,100,0, ( struct sockaddr *) &cliaddr, &len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	sendto(sockfd, hello_msg,strlen(hello_msg),0, (struct sockaddr *) &cliaddr, len);
		
	return 0;
}

