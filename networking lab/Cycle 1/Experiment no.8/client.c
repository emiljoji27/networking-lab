#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8000

void main(int argc, char *argv[])
{
    int client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *buff = malloc(6 * sizeof(char));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int PORT1;
    char *body = malloc(100 * sizeof(char));

    while (1)
    {
        if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("Socket creation failed!\n");
            exit(1);
        }

        int opt = 1;
        setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (void *)&opt, sizeof(opt));

        printf("Enter web server port and request: ");
        scanf("%d %s", &PORT1, buff);

        if (connect(client_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            printf("Connection failed!\n");
            exit(1);
        }

        if (send(client_fd, &PORT1, sizeof(int), 0) < 0)
        {
            printf("Sending failed!\n");
            exit(1);
        }
        else
        {
            if (send(client_fd, buff, 6 * sizeof(char), 0) < 0)
            {
                printf("Sending failed!\n");
                exit(1);
            }
            else
            {
                if (!strcmp(buff, "post") || !strcmp(buff, "put") || !strcmp(buff, "patch"))
                {
                    printf("Enter body: ");
                    scanf("\n");
                    fgets(body, 100, stdin);
                    body[strlen(body) - 1] = '\0';

                    if (send(client_fd, body, 100 * sizeof(char), 0) < 0)
                    {
                        printf("Sending failed!\n");
                        exit(1);
                    }
                }

                printf("Request sent: %s\n", buff);

                if (recv(client_fd, body, 100 * sizeof(char), 0) < 0)
                {
                    printf("Receive failed!\n");
                    exit(1);
                }
                else
                {
                    printf("Response body: %s", body);
                }
            }
        }

        close(client_fd);
    }
}
