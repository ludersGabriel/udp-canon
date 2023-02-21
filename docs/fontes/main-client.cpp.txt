#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "client.h"
#include "message.h"

int main(int argc, char** argv) {
  if(argc < 5 || argc > 6) {
    fprintf(stdout, "Usage: client <server> <port> <clients> <cannonballs> [file]\n");
    exit(1);
  }

  char* server = argv[1];
  char* port = argv[2];
  char* clients = argv[3];
  char* cannonballs = argv[4];

  FILE* output = stdout;
  if(argc == 6) {
    output = fopen(argv[5], "w");
    if(!output){
      fprintf(stdout, "Error opening file %s\n", argv[5]);
      exit(1);
    }
  }

  handshake(server, port, clients, cannonballs, output);
  fflush(output);

  int pid = 0;
  int clientsAmount = atoi(clients);
  vector<int> pids;
  do {
    pid = fork();
    pids.push_back(pid);
  }while(pid && --clientsAmount);

  if(pid) {
    parentMain(pids, output);
    return 0;
  }

  childMain(atoi(cannonballs), server, port);

  return 0;
}