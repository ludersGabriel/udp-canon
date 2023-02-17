#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "client.h"
#include "message.h"

int main(int argc, char** argv) {
  if(argc != 5) {
    printf("Usage: client <server> <port> <clients> <cannonballs>\n");
    exit(1);
  }

  int pid = 0;
  int clients = atoi(argv[3]);
  do {
    pid = fork();
  }while(pid && --clients);

  if(pid) {
    printf("client: forked all cannonballs\n");
    return 0;
  }

  int cannonballs = atoi(argv[4]);
  int myPid = getpid();

  Client* client = clientConstructor((char*)argv[1], (char*)argv[2]);

  for(int i = 1; i <= cannonballs; i++){
    char text[30];
    sprintf(text, "cannonball %d", i);
    Message* msg = messageConstructor(text, i, myPid);

    sendToServer(client, msg);
    printf("fork %d: sent %s\n", msg->clientPid, msg->message);

    messageDestructor(msg);
  }
  
  clientDestructor(client);

  return 0;
}