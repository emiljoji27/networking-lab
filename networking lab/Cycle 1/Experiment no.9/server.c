#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

void print_err(char *msg)
{
  printf("%s\n",msg);
  exit(1);
}

void main() 
{
	int server_fd, code;
	struct sockaddr_in serv_addr, cli_addr;
	
	int PORT;
	
	printf("Enter port number of time server : ");
    scanf("%d",&PORT);
	
	printf("Concurrent Time Server\n");
	
	if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
       print_err("Socket creation failed!");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);
	
	if(bind(server_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) 
       print_err("Binding failed!");
	
	int len = sizeof(cli_addr);
	
	while(1) 
    {
    		if(recvfrom(server_fd, &code, sizeof(int), 0, (struct sockaddr*) &cli_addr, &len) < 0) 
                 print_err("Receive failed!");
            else if (fork() == 0) 
            {
			     printf("Received time request.\n");
			
			     time_t now = time(0);
			     char* str = ctime(&now);
			 
			     if(sendto(server_fd, str, (strlen(str) + 1) * sizeof(char), 0, (struct sockaddr*) &cli_addr, len) < 0) 
                        print_err("Sending failed");
                 else 
				        printf("Time reply sent.\n");
			    
    		}
    	}
    	
    	close(server_fd);
}
