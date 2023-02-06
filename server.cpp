#include "server.h"

Server* serverConstructor(char* port, bool udp){
  Server* server = (Server*) malloc(sizeof(Server));
  server->isUDP = udp;

  gethostname(server->hostname, MAXHOSTNAME);

  server->hostInfo = gethostbyname(server->hostname);
  if(!server->hostInfo){
    printf( "Server: couldn't get my IP\n");
    exit(1);
  }

  server->serverAddress.sin_port = htons(atoi(port));
  bcopy(
    (char*) server->hostInfo->h_addr,
    (char*) &(server->serverAddress.sin_addr),
    server->hostInfo->h_length
  );
  server->serverAddress.sin_family = server->hostInfo->h_addrtype;

  int type = udp ? SOCK_DGRAM : SOCK_STREAM;
  server->listenSocket = socket(server->hostInfo->h_addrtype, type, 0);
  if(server->listenSocket < 0){
    printf( "Server: couldn't open listen socket\n");
    exit(1);
  }

  int ret = bind(
    server->listenSocket,
    (struct sockaddr*) &(server->serverAddress),
    sizeof(server->serverAddress)
  );
  if(ret < 0){
    printf( "Server: couldn't bind to socket\n");
    exit(1);
  }

  return server;
}

void serverDestructor(Server* server){
  close(server->listenSocket);
  free(server);
}

void receiveFromClient(Server* server){
  int i = sizeof(server->clientAddress);
  recvfrom(
    server->listenSocket,
    server->buffer,
    BUFSIZ,
    0,
    (struct sockaddr*) &(server->clientAddress),
    (socklen_t*) &i
  );
  printf( "Server: received '%s'\n", server->buffer);
}

void sendToClient(Server* server){
  sendto(
    server->listenSocket,
    server->buffer,
    BUFSIZ,
    0,
    (struct sockaddr*) &(server->clientAddress),
    sizeof(server->clientAddress)
  );
}