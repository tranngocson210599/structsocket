#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 7473
#define MAX 1024
char client_message[2000];
//char buffer[1024] = "Message from server";
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//void ChatWithClient(int serverSocket, struct sockaddr_in address) {
  void * ChatWithClient(void *arg) {
    
  char buffC[MAX];
  char buffS[MAX];
  int n;
  int serverSocket=*((int*)arg);
  for (;;) {
    read(serverSocket, buffC, sizeof(buffC));
    printf("Message from Client : %s", buffC);
    if ((strncmp(buffC, "exit", 4)) == 0) {
      printf("Client  exit...\n");// inet_ntoa(address.sin_addr));
      break;
    }
  
  
  }
  /*
 int newSocket = *((int *)arg);
  recv(newSocket, client_message, 2000, 0);
  printf("%s\n", client_message);
  pthread_mutex_lock(&lock);
  int n=0;
  while ((buffer[n++] = getchar()) != '\n')
  pthread_mutex_unlock(&lock);
  sleep(1);
  send(newSocket, buffer, strlen(buffer), 0);
  printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
  */
}

int main(int argc, char *argv[]) {
  int master_socket, addrlen, new_socket, client_socket[30];
  int max_clients = 30, activity, i, valread, sd;
  int max_sd;
  struct sockaddr_in address;
  struct timeval time_out;
  time_out.tv_usec = 0;
  char buffer[1025];

  fd_set readfds;

  for (i = 0; i < max_clients; i++) {
    client_socket[i] = 0;
  }

  if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(master_socket, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  double time_tmp;
  addrlen = sizeof(address);
   pthread_t tid[3];
  while (1) {
   // printf("Waiting Client .....\n");
    time_out.tv_sec = 10;
    //time_out.tv_sec =time(0);
    //time_tmp=difftime(time_out.tv_sec,0);
    FD_ZERO(&readfds);

    FD_SET(master_socket, &readfds);
    max_sd = master_socket;
    //
    //clock_t begin = clock();
    activity = select(max_sd + 1, &readfds, NULL, NULL, &time_out);
    // server khong nhan duoc request tu client thi readfds khong con chua master_socket nua
    if ((activity < 0) && (errno != EINTR)) {
      printf("select error");
    }
   // clock_t end = clock();
   // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    if (activity == 0) {
      printf("\n Server Exit \n");
      break;
    }
    if (FD_ISSET(master_socket, &readfds)) {
      if ((new_socket = accept(master_socket, (struct sockaddr *)&address,
                               (socklen_t *)&addrlen)) < 0)

      {
        perror("accept");
        exit(EXIT_FAILURE);
      }
     pthread_create(&tid[i++], NULL, ChatWithClient, &new_socket);
      if (i >= 3) 
     {
       i = 0;
       while (i < 3) 
        {
         pthread_join(tid[i++], NULL);
        }
       i = 0;
      }
    }
      for (i = 0; i < max_clients; i++) {

        if (client_socket[i] == 0) {
          client_socket[i] = new_socket;
          break;
        }
      }
    }
  

  return 0;
}

