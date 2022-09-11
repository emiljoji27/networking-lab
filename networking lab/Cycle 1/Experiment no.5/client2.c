#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8080

void err_handle(char *msg)
{
  printf("%s\n",msg);
  exit(-1);
}


void main()
{
	int sock_fd, valread, client_fd,n,num;
	float num1;
	struct sockaddr_in cli_addr;
	char buffer[100];
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd<0)
	   err_handle("Socket creation failed");

	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &cli_addr.sin_addr) <= 0) 
	        err_handle("\nInvalid address / Address not supported \n");

        client_fd = connect(sock_fd, (struct sockaddr*) &cli_addr,sizeof(cli_addr));
        if(client_fd<0)
            err_handle("\nConnection Failed \n");   
        while(1)
        {
        valread = read(sock_fd, &n, sizeof(int));  
        if(n==1)
        {
	  printf("Server sending a string...");
	  valread = read(sock_fd,buffer,100);
          printf("%s\n\n",buffer);
        }
	else if(n==2)   
	{
	  printf("Server sending an integer...\n");
	  valread = read(sock_fd,&num,sizeof(int));
          printf("The Square of the Integer : %d\n\n",num);
	}
	else if(n==3)   
	{
	  printf("Server sending a floating point number...\n");
	  valread = read(sock_fd,&num1,sizeof(float));
	  printf("The increased value : %f\n\n",num1);
	}
	else if(n==4)
	{
	  printf("\nExiting...\n");
	  exit(1);
	}

        
        }
        close(client_fd);
}

