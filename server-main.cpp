#include <iostream>
#include <bits/stdc++.h>
#include <signal.h>
#include <unistd.h>

#include "server.h"
#include "message.h"

using namespace std;

bool isDone = false;

void resolveTimer(int signum){
  isDone = true;
}

int main(int argc, char** argv) {
  if(argc < 2 || argc > 3) {
    fprintf(stdout, "Usage: server <port> [file]\n");
    exit(1);
  }
  
  char* port = argv[1];

  FILE *output = stdout;
  if(argc == 3) {
    output = fopen(argv[2], "w");
    if(!output){
      fprintf(stdout, "Error opening file %s\n", argv[2]);
      exit(1);
    }
  }

  Server* server = serverConstructor((char*)port, isDone, output);

  struct sigaction action;
  action.sa_handler = resolveTimer;
  sigemptyset (&action.sa_mask) ;
  action.sa_flags = 0 ;
  sigaction (SIGALRM, &action, 0);

  fprintf(server->output, "server: now waiting messages...\n");
  for(;!isDone;){
    alarm(7);
    receiveFromClient(server);
    alarm(0);
    sendToClient(server);
  }

  printReport(server);
  printLossReport(server);
  verifyOrder(server);
  writeReceivedFile(server);
  appendGeneralReport(server);
  printFooter(server);
  
  serverDestructor(server);

  return 0;
}
