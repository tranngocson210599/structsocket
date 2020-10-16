

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 1024
void ChatWithServer(int clientSocket) 
{ 
    char buffC[MAX]; 
    char buffS[MAX]; 
    int n; 
    for (;;) { 
        bzero(buffC, sizeof(buffC)); 
        printf("Send message to Server : "); 
        n = 0; 
        
        while ((buffC[n++] = getchar()) != '\n');  
         if ((strncmp(buffC, "exit", 4)) == 0) { 
             send(clientSocket, buffC, sizeof(buffC), 0); 
            printf("Client Exit...\n"); 
            break; 
        } 
        send(clientSocket, buffC, sizeof(buffC), 0); 
       // read(clientSocket, buffS, sizeof(buffS));
       // printf("Message from Server : %s", buffS);     
       
    } 
} 
char client_ser[2000];
void *rev(void *arg) 
{
  int newSocket = *((int *)arg);
 // recv(newSocket, client_message, 2000, 0);
 // printf("%s\n", client_message);
 // pthread_mutex_lock(&lock);
  
   for (;;) {
    //recv(newSocket, client_ser, 2000, 0);
    read(newSocket, client_ser, sizeof(client_ser));
    printf("%s\n", client_ser);
   // send(newSocket, client_message, strlen(client_message), 0);
   // if ((strncmp(client_ser, "exit", 4)) == 0 ||(strncmp(client_message, "", 4)) == 0) {
   //   printf("Client  exit...\n");// inet_ntoa(address.sin_addr));
   //   break;
    
   // }
    }
 // while ((buffer[n++] = getchar()) != '\n')
 // pthread_mutex_unlock(&lock);
//  sleep(1);
 // send(newSocket, buffer, strlen(buffer), 0);
 // printf("Exit socketThread \n");
  close(newSocket);
  pthread_exit(NULL);
}
int main() {
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char buffS[MAX];
  char buffC[MAX] = "client";
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(7799);

  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
  ChatWithServer(clientSocket);
  pthread_t rev_t;
  pthread_create(&rev_t,NULL,rev,&clientSocket);
  pthread_join(rev_t,NULL);
  close(clientSocket);
}
