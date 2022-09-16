#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define PORT 8080

typedef struct recvData 
{
  int n;
  int i; 
  int* client_fd;
  int* status;
} recvData;


void err_handle(char *msg)
{
  printf("%s\n",msg);
  exit(-1);
} 


void* serverRecv(void* data) 
{
  char str[100];
  recvData d = *((recvData*) data);
  while(1) 
  {
    int k = recv(d.client_fd[d.i], str, 100 * sizeof(char), 0);
    if(k < 0)
        err_handle("Receive failed!\n");
    else if(k == 0) 
    {
      printf("Client %d exited\n", d.i + 1);
      d.status[d.i] = 0;
      for(int j = 0; j < d.n; j++) 
      {
        if(j != d.i && d.status[j] != 0) 
        {
          sprintf(str, "Client %d exited", d.i + 1);
          if(send(d.client_fd[j], str, (strlen(str) + 1) * sizeof(char), 0) < 0) 
	        err_handle("Send failed!\n");
        }
      }
      break;
     } 
     else
       printf("Received message from client %d: %s\n", d.i + 1, str);
		
     for(int j = 0; j < d.n; j++) 
     {
       if(j != d.i && d.status[j] != 0)
        {
          char str1[120];
	      sprintf(str1, "Client %d: ", d.i + 1);
	      strcat(str1, str);
	      if(send(d.client_fd[j], str1, (strlen(str1) + 1) * sizeof(char), 0) < 0)
	         err_handle("Send failed!");
	     else 
	         printf("Message sent to client %d.\n", j + 1);
		 }
      }
   }
}

void main() 
{
  int server_fd, n;
  struct sockaddr_in address, cli_addr1, cli_addr2;
  int addrlen = sizeof(address);
  printf("\t\t======CHAT SERVER======\n");
  printf("Enter no. of clients: ");
  scanf("%d", &n);
  int client_fd[n], status[n];
  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
     err_handle("Socket creation failed!\n");
  else 
     printf("Server socket created.\n");
	
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  
  if(bind(server_fd, (struct sockaddr*) &address, addrlen) < 0)
     err_handle("Socket binding failed!\n");
  else 
     printf("Socket binded.\n");
	
  if(listen(server_fd, n) < 0) 
     err_handle("Listening failed!\n");
  else 
     printf("Server listening.\n");
	
  for(int i = 0; i < n; i++) 
  {
    if((client_fd[i] = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0)
	  err_handle("Connection failed!\n");
    else 
    {
	printf("Connected to client %d.\n", i+1);
	status[i] = 1;
    }
  }
	
  pthread_t tid[n];
  recvData data[n];
	
  for(int i = 0; i < n; i++) 
  {
    data[i].i = i;
    data[i].n = n;
    data[i].client_fd = client_fd;
    data[i].status = status;
    pthread_create(&tid[i], NULL, serverRecv, &data[i]);
  }
  
  for (int i = 0; i < n; i++)
    pthread_join(tid[i], NULL);
	
  for(int i = 0; i < n; i++) 
    close(client_fd[i]);
  
  close(server_fd);
}
