// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

struct Student
{
    int Id;
    char Name;
};

unsigned char * serialize_int(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 24;
  buffer[1] = value >> 16;
  buffer[2] = value >> 8;
  buffer[3] = value;
  return buffer + 4;
}

unsigned char * serialize_char(unsigned char *buffer, char value)
{
  buffer[0] = value;
  return buffer + 1;
}

unsigned char * serializeStudent(unsigned char *buffer, struct Student value)
{
  buffer = serialize_int(buffer, value.Id);
  buffer = serialize_char(buffer, value.Name);
 //for(int i=0; i<strlen(value.Name); i++)
 //   buffer = serialize_char(buffer,value.Name[i]);
  return buffer;
}




int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	//char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
    /////
    struct Student  mess;
    mess.Id=17520992;
    mess.Name='s';
      unsigned char buffer[32], *ptr;
    ptr = serializeStudent(buffer, mess);
    send(sock, buffer, ptr - buffer, 0);
   // serializeStudent(buff,mess);
    //buff=serializeStudent(buff,mess);
	//send(sock , buff , strlen(buff) , 0 ); 
   // send(sock , hello , strlen(hello) , 0 ); 
//	valread = read( sock , buffer, 1024); 
//	printf("%s\n",buffer ); 
	return 0; 
} 
