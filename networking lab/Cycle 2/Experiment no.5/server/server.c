#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


char str[100];
char str1[1000];
int client_fd;

void print_err(char *msg)
{
  printf("%s\n",msg);
  exit(1);
}

void ftp_get()
{
        DIR *d;
		struct dirent *dir;
		d = opendir(".");
		str1[0] = '\0';
		
		if (d) 
        {
			while((dir = readdir(d)) != NULL) 
            {
				if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..") && strcmp(dir->d_name, "server.c") && strcmp(dir->d_name, "server")) 
                {
					strcat(str1, dir->d_name);
					strcat(str1, "\n");
				}
			}
			closedir(d);
		}
		
		if(send(client_fd, str1, 1000 * sizeof(char), 0) <= 0) {
			printf("GET failed!\n");
			return;
		}
		
		if(send(client_fd, "200 OK", 7 * sizeof(char), 0) <= 0) {
			printf("GET failed!\n");
			return;
		} 
        else {
			printf("GET successful!\n");
			return;
		}  

}

void ftp_upload()
{
       if(recv(client_fd, str, 100 * sizeof(char), 0) <= 0) {
			printf("UPLOAD failed!\n");
			return;
		}
		
		if(recv(client_fd, str1, 1000 * sizeof(char), 0) <= 0) {
			printf("UPLOAD failed!\n");
			return;
		}
		
		FILE* fp = fopen(str, "w");
		fputs(str1, fp);
		fclose(fp);
		
		if(send(client_fd, "200 OK", 7 * sizeof(char), 0) <= 0) {
			printf("UPLOAD failed!\n");
			return;
		} 
        else {
			printf("UPLOAD successful!\n");
			return;
		}

}

void ftp_download()
{
       if(recv(client_fd, str, 100 * sizeof(char), 0) <= 0) {
			printf("DOWNLOAD failed!\n");
			return;
		}
		
		FILE* fp = fopen(str, "r");
		
		if(fp == NULL) {
			str1[0] = '\0';
			
			if(send(client_fd, str1, sizeof(char), 0) <= 0) {
				printf("DOWNLOAD failed!\n");
				return;
			}
			
			if(send(client_fd, "400 BAD", 8 * sizeof(char), 0) <= 0) {
				printf("DOWNLOAD failed!\n");
				return;
			}
			
			return;
		}
		
		str1[0] = '\0';
		
		while(fgets(str, 100, fp) != NULL)
			strcat(str1, str);
		
		fclose(fp);
		
		if(send(client_fd, str1, 1000 * sizeof(char), 0) <= 0) {
			printf("DOWNLOAD failed!\n");
			return;
		}
		
		if(send(client_fd, "200 OK", 7 * sizeof(char), 0) <= 0) {
			printf("DOWNLOAD failed!\n");
			return;
		} 
        else {
			printf("DOWNLOAD successful!\n");
			return;
		}


}

void ftp_rename()
{
        if(recv(client_fd, str, 100 * sizeof(char), 0) <= 0) {
			printf("RENAME failed!\n");
			return;
		}
		
		if(recv(client_fd, str1, 100 * sizeof(char), 0) <= 0) {
			printf("RENAME failed!\n");
			return;
		}
		
		if(!rename(str, str1)) {
			if(send(client_fd, "200 OK", 7 * sizeof(char), 0) <= 0) {
				printf("RENAME failed!\n");
				return;
			}
		} 
        else {
			if(send(client_fd, "400 BAD", 8 * sizeof(char), 0) <= 0) {
				printf("RENAME failed!\n");
				return;
			} 
            else {
				printf("RENAME successful!\n");
				return;
			}
		}
}

void ftp_delete()
{
        if(recv(client_fd, str, 100 * sizeof(char), 0) <= 0) {
			printf("DELETE failed!\n");
			return;
		}
		
		if(!remove(str)) {
			if(send(client_fd, "200 OK", 7 * sizeof(char), 0) <= 0) {
				printf("DELETE failed!\n");
				return;
			}
		} 
        else {
			if(send(client_fd, "400 BAD", 8 * sizeof(char), 0) <= 0) {
				printf("DELETE failed!\n");
				return;
			} 
            else {
				printf("DELETE successful!\n");
				return;
			}
		}
}

void main() 
{
	int PORT=8080;
	
	int server_fd;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
	printf("FTP Server\n");
	
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
         print_err("Socket creation failed!");
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	if(bind(server_fd, (struct sockaddr*) &address, addrlen) < 0) 
        print_err("Socket binding failed!");
	
	if(listen(server_fd, 5) < 0) 
        print_err("Listening failed!");
	
	while(1) 
    {
		if((client_fd = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0)
            print_err("Connection failed!");
        else
			printf("Connected to client.\n");
		
	    if(recv(client_fd, str, 100 * sizeof(char), 0) <= 0) 
		   printf("Connection lost!");
		
        if(!strcmp(str, "GET"))
           ftp_get();

        else if(!strcmp(str, "UPLOAD")) 
           ftp_upload();

        else if(!strcmp(str, "DOWNLOAD"))
            ftp_download();

        else if(!strcmp(str, "RENAME")) 
            ftp_rename();

        else if(!strcmp(str, "DELETE"))
            ftp_delete();

        else 
            printf("Invalid request from client!\n");

		close(client_fd);
	}
	
	close(server_fd);
}
