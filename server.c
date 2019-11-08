#include <stdio.h>    
#include <sys/socket.h>    
#include <arpa/inet.h>    
#include <stdlib.h>    
#include <string.h>    
#include <unistd.h>   

#define MAXPENDING 5     
#define RCVBUFSIZE 32

int main(int argc, char *argv[]) {
int servSock;   
int clntSock;   
struct sockaddr_in  echoServAddr; 
struct sockaddr_in   echoClntAddr; 
unsigned short echoServPort;   
unsigned int clntLen;   
char echoBuffer[RCVBUFSIZE];
int recvMsgSize; 

if (argc != 2) { 
fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
exit(1);
}

echoServPort = atoi(argv[1]); 

if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
perror("socket() failed");


memset(&echoServAddr, 0, sizeof(echoServAddr));  
echoServAddr.sin_family= AF_INET; 
echoServAddr.sin_addr.s_addr= htonl(INADDR_ANY);    
echoServAddr.sin_port= htons(echoServPort);


if (bind(servSock, (struct sockaddr*) &echoServAddr, sizeof(echoServAddr)) < 0)
perror("bind() failed");


if (listen(servSock, MAXPENDING) < 0)
perror("listen() failed");

printf("server: waiting for connections...\n");
for (;;) 
{

clntLen= sizeof(echoClntAddr);

if ((clntSock = accept(servSock, (struct sockaddr*) &echoClntAddr,&clntLen)) < 0)
perror("accept() failed");

memset(echoBuffer, '\0',RCVBUFSIZE);
if ((recvMsgSize= recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
perror("recv() failed");

while (recvMsgSize>0)
  {
   puts(echoBuffer);
   if (send(clntSock, echoBuffer, recvMsgSize, 0) != recvMsgSize)
   perror("send() failed");
   memset(echoBuffer, '\0',RCVBUFSIZE);

  if ((recvMsgSize= recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
    perror("recv() failed");
   }
if(close(clntSock) == 0)    
printf("close connection with %d \n", clntSock);


}

}




