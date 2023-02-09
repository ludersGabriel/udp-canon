#include "client.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if(argc != 4) {
    printf("Usage: client <server> <port> <cannonballs>\n");
    exit(1);
  }
  
  Client* client = clientConstructor((char*)argv[1], (char*)argv[2]);
  int cannonballs = atoi(argv[3]);

  for(int i = 1; i <= cannonballs; i++){
    char msg[100];
    sprintf(msg, "cannonball [%d]", i);
    sendToServer(client, (char*)msg);
    printf("client: sent %s\n", msg);
  }
  
  clientDestructor(client);

  return 0;
}