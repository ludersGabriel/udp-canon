#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "client.h"
#include "message.h"

int main(int argc, char** argv) {
  if(argc != 5) {
    printf("Usage: client <server> <port> <clients> <cannonballs>\n");
    exit(1);
  }

  char* server = argv[1];
  char* port = argv[2];
  char* clients = argv[3];
  char* cannonballs = argv[4];

  handshake(server, port, clients, cannonballs);

  int pid = 0;
  int clientsAmount = atoi(clients);
  vector<int> pids;
  do {
    pid = fork();
    pids.push_back(pid);
  }while(pid && --clientsAmount);

  if(pid) {
    parentMain(pids);
    return 0;
  }

  childMain(atoi(cannonballs), server, port);

  return 0;
}