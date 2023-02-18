
#include <stdlib.h>
#include "client.h"

Client* clientConstructor(char* svName, char* port, bool udp) {
  Client *client = (Client*) malloc(sizeof(Client));

  client->host = svName;
  client->hp = gethostbyname(client->host);
  if(!client->hp){
    printf( "client: host %s not found\n", client->host);
    exit(1);
  }

  bcopy(
    (char*) client->hp->h_addr, 
    (char*) &(client->address.sin_addr), 
    client->hp->h_length
  );
  client->address.sin_family = client->hp->h_addrtype;

  client->address.sin_port = htons(atoi(port));

  int type = udp ? SOCK_DGRAM : SOCK_STREAM;
  client->socketDescriptor = socket(client->hp->h_addrtype, type, 0);
  if(client->socketDescriptor < 0){
    printf( "client: not able to open socket");
    exit(1);
  }

  return client;
}

void clientDestructor(Client* client) {
  close(client->socketDescriptor);
  free(client);
}

void sendToServer(Client* client, Message* msg) {

  int ret = sendto(
    client->socketDescriptor,
    msg,
    sizeof(Message),
    0,
    (struct sockaddr*) &(client->address),
    sizeof(client->address)
  );

  if(ret != sizeof(Message)){
    printf("client: couldn't send whole message\n");
    exit(1);
  }
}