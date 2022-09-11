#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void print_err(char *msg)
{
  printf("%s\n",msg);
  exit(1);
}

void main() 
{
	struct sockaddr_in serv_addr;
	int client_fd, PORT, code = 200, len = sizeof(serv_addr);
	char time[30];
	
	printf("Time Client\n");
	
	if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
        print_err("Socket creation failed!");
	
	while(1) 
    {
		printf("Enter Time Server port: ");
		scanf("%d", &PORT);

        if(PORT==-100)
           break;
		
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(PORT);
		
		if(sendto(client_fd, &code, sizeof(int), 0, (struct sockaddr*) &serv_addr, len) < 0) 
             print_err("Sending failed!");
        else 
        {
			if(recvfrom(client_fd, time, 30 * sizeof(char), 0, (struct sockaddr*) &serv_addr, &len) < 0) 
                 print_err("Receive failed!");
            else 
				 printf("Received time from Time Server %d: %s", PORT, time);
		}
	}
	
    close(client_fd);
}

