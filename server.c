#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

char client_message[2000];
char buffer[1024];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *SocketThread(void *arg) 
{
  int newSocket = *((int *)arg);
 // recv(newSocket, client_message, 2000, 0);
 // printf("%s\n", client_message);
 // pthread_mutex_lock(&lock);
  int n=0;
  int rev_size;
   for (;;) {
    rev_size=recv(newSocket, client_message, 2000, 0);
    printf("%s", client_message);
    send(newSocket, client_message, strlen(client_message), 0);
    if ((strncmp(client_message, "exit", 4)) == 0 || rev_size == 0) 
    {
      printf("Client  exit...\n");// inet_ntoa(address.sin_addr));
      break;
    
    }
    }
 // while ((buffer[n++] = getchar()) != '\n')
 // pthread_mutex_unlock(&lock);
//  sleep(1);
 //  send(newSocket, buffer, strlen(buffer), 0);
 // printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
}

int main() 
{

  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  serverSocket = socket(PF_INET, SOCK_STREAM, 0);

  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(7799);

  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  listen(serverSocket, 50);
 fd_set readfds;
  pthread_t tid[3];
  int i = 0;
  int max_sd;
  int activity;
  int master_socket;
  while (1) 
  {

    addr_size = sizeof serverStorage;
    //accept all request
	FD_ZERO(&readfds);

    FD_SET(serverSocket, &readfds);
    max_sd = serverSocket;
    //
    //clock_t begin = clock();
    activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
	 if (FD_ISSET(serverSocket, &readfds)) 
//	{
    newSocket = accept(serverSocket, (struct sockaddr *)&serverStorage, &addr_size);
	 
    pthread_create(&tid[i++], NULL, SocketThread, &newSocket);
    
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
    send(newSocket, client_message, strlen(client_message), 0);
  return 0;
 // }
}
