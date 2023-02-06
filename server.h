
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define QUEUESIZE 5
#define MAXHOSTNAME 30

typedef struct SERVER {
  int listenSocket;
  char buffer[BUFSIZ + 1];

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  struct hostent* hostInfo;
  char hostname[MAXHOSTNAME];
  bool isUDP;

} Server;

Server* serverConstructor(char* port, bool udp = true);
void serverDestructor(Server* server);
void listenToClients(Server* server);
void acceptClient(Server* server);
void receiveFromClient(Server* server);
void sendToClient(Server* server);