#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
# include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>
#define IP 0
#define MAX 5

sem_t mutex;

int ports[] = {8001, 8002, 8003, 8004, 8005};
int pid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const int THINKING = 2;
const int HUNGRY = 1;
const int EATING = 0;
const int AVAILABLE = 1;
const int OCCUPIED = 0;
const int REQUEST = 1;
const int RELEASE = 0;
const int GRANTED = 1;
const int REJECTED = 0;


void display(int id, int state){
    if(state == EATING){
        printf("Philosopher %d is Eating\n",id);
    }else if(state == THINKING){
        printf("Philosopher %d is Thinking\n",id);
    }else if(state == HUNGRY){
        printf("Philosopher %d is Hungry\n",id);
    }
}

int fork_network_call(int i, int port){
    int fd = socket(AF_INET, SOCK_STREAM, IP);
    if(fd == -1){
		perror("Socket Creation Error");
        printf("\nFork %d", i);
		exit(EXIT_FAILURE);
	}
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    int addrlen = sizeof(address);
    if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Binding Failed");
        exit(EXIT_FAILURE);
    }
    listen(fd,5);
    return fd;
}


int philosopher_network_call(int id, int fork, int port){
    int fd = socket(AF_INET, SOCK_STREAM, IP);
     if(fd == -1){
		perror("Socket Creation Error");
        printf("\nPhilosopher %d",id);
		exit(EXIT_FAILURE);
	}
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if(connect(fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Connection Error");
        printf("\nPhilosopher %d",id);
		exit(EXIT_FAILURE);
    }
    return fd;
}

int acquire_fork(int id, int fork, int port){
    int fd = philosopher_network_call(id,fork, port);
    int command = REQUEST;
    write(fd, &command, sizeof(command));
    write(fd, &id,sizeof(id));
    read(fd, &command, sizeof(command));
    close(fd);
    return command;
}

int release_fork(int id, int fork, int port){
    int fd = philosopher_network_call(id,fork, port);
    int command = RELEASE;
    write(fd, &command, sizeof(command));
    write(fd, &id,sizeof(id));
    read(fd, &command, sizeof(command));
    close(fd);
    return command;
}

int compute_left_fork(int id){
    return id;
}

int compute_right_fork(int id){
    return (id+1)%MAX;
}

void test(int id, int * state, int left, int right){
    if(*state != HUNGRY) return;
    int res_left  = acquire_fork(id,left,ports[left]);
    if(res_left != GRANTED) return;
    int res_right = acquire_fork(id,right, ports[right]);
    if(res_right != GRANTED){
        release_fork(id,left,ports[left]);
        return;
    }
    *state = EATING;
    display(id,*state);
    sleep(rand()%3+2);
}

void take_fork(int id, int * state, int left, int right){
    if(*state != HUNGRY){
        *state = HUNGRY;
        display(id,*state);
    }
    sem_wait(&mutex);
    test(id,state,left,right);
    sem_post(&mutex);
    sleep(rand()%3+2);
}

void put_fork(int id, int * state, int left, int right){
    sem_wait(&mutex);
    if(*state != THINKING){
        *state=THINKING;
        display(id,*state);
    }
    release_fork(id,left,ports[left]);
    release_fork(id,right,ports[right]);
    sleep(rand()%3+2);
    sem_post(&mutex);
}

void philosopher_start(int id){
    int state = THINKING;
    display(id,state);
    int left = compute_left_fork(id);
    int right = compute_right_fork(id);
    while(true){
        take_fork(id, &state, left, right);
        put_fork(id, &state, left, right);
    }
}

void fork_start(int id){
    printf("Fork %d\n",id);
    int fork_id = fork_network_call(id, ports[id]);
    int state = AVAILABLE;
    int command, philosopher;
    while (true){
        // int clientfd = accept(fork_id, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        int clientfd = accept(fork_id, NULL, NULL);
        if (clientfd < 0) {
		    perror("Accept Failed");
		    exit(EXIT_FAILURE);
	    }
        read(clientfd, &command, sizeof(command));
        read(clientfd, &philosopher, sizeof(philosopher));
        if(command == REQUEST){
            if(state == AVAILABLE){
                state = OCCUPIED;
                command = GRANTED;
                write(clientfd, &command, sizeof(command));
            }else{
                command = REJECTED;
                write(clientfd, &command, sizeof(command));
            }
        }else if(command == RELEASE){
            state = AVAILABLE;
            command = GRANTED;
            write(clientfd, &command, sizeof(command));
        }
    }
}

void main() {
    sem_init(&mutex, 1, 1);
    if(pid[0]=fork()==0){
        fork_start(0);
        exit(EXIT_SUCCESS);
    }else if(pid[1]=fork()==0){
        fork_start(1);
        exit(EXIT_SUCCESS);
    }else if(pid[2]=fork()==0){
        fork_start(2);
        exit(EXIT_SUCCESS);
    }else if(pid[3]=fork()==0){
        fork_start(3);
        exit(EXIT_SUCCESS);
    }else if(pid[4]=fork()==0){
        fork_start(4);
        exit(EXIT_SUCCESS);
    }

    sleep(2);

    if(pid[5]=fork()==0){
        philosopher_start(0);
        exit(EXIT_SUCCESS);
    }else if(pid[6]=fork()==0){
        philosopher_start(1);
        exit(EXIT_SUCCESS);
    }else if(pid[7]=fork()==0){
        philosopher_start(2);
        exit(EXIT_SUCCESS);
    }else if(pid[8]=fork()==0){
        philosopher_start(3);
        exit(EXIT_SUCCESS);
    }else if(pid[9]=fork()==0){
        philosopher_start(4);
        exit(EXIT_SUCCESS);
    }
    sleep(60);
    for(int i = 0; i< 10;i++){
        kill(pid[i],SIGQUIT);
    }
    wait(NULL);
}
