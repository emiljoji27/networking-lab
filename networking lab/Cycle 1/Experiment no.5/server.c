#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <math.h>
#define PORT 8080


void err_handle(char *msg)
{
  printf("%s\n",msg);
  exit(-1);
} 

void main()
{
	int server_fd, new_socket,new_socket1, valread,n,num;
	char msg[30],buffer[100],rev_buff[100];
	float num1;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd<0)
	   err_handle("Socket creation failed");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr*) &address,sizeof(address)) < 0) 
	       err_handle("Bind failed");
	       
	listen(server_fd, 3);
	new_socket = accept(server_fd, (struct sockaddr*) &address,(socklen_t*) &addrlen);
	new_socket1 = accept(server_fd, (struct sockaddr*) &address,(socklen_t*) &addrlen);
	if(new_socket<0)
	      err_handle("Accepting connection failed");
	while(1)
	{ 
	printf("\n1.String reversal\n2.Square of Integer\n3.Power of Float\n4.Exit\nSelect the option : ");
	scanf("%d",&n);
	if(n==4) 
	{
	  printf("\nExiting...\n");
	  write(new_socket, &n , sizeof(int));
	  write(new_socket1, &n , sizeof(int));
	  exit(1);
	}
	else if(n!=1 && n!=2 && n!=3)
	{
	  printf("Invalid Option!");
	  exit(-1);
	}
	write(new_socket, &n , sizeof(int));
	write(new_socket1, &n , sizeof(int));
	
	if(n==1)
	{
	  bzero(buffer,100);  
	  valread = read(new_socket,buffer,100);
	  int j=0;
	  for(int i=strlen(buffer)-1;i>=0;i--)
	  {
	    rev_buff[j]=buffer[i];
	    j++;
	  }
	  write(new_socket1, rev_buff , strlen(rev_buff));
	}
	else if(n==2)   
	{
	 valread = read(new_socket,&num,sizeof(int));
	 num=num*num;
	 write(new_socket1, &num , sizeof(int));
	}
	else
	{ 
	 valread = read(new_socket,&num1,sizeof(float));
	 num1=pow(num1,1.5);
	 write(new_socket1, &num1 , sizeof(float));
	}
	}
	
       close(new_socket);
       shutdown(server_fd, SHUT_RDWR);
}

