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
    printf("Usage: server <port> [silent]\n");
    exit(1);
  }
  
  char* port = argv[1];
  bool silent = argc == 3 ? true : false;

  Server* server = serverConstructor((char*)port, isDone, silent);

  struct sigaction action;
  action.sa_handler = resolveTimer;
  sigemptyset (&action.sa_mask) ;
  action.sa_flags = 0 ;
  sigaction (SIGALRM, &action, 0);

  if(!silent)
    printf("server: now waiting messages...\n");
  for(;!isDone;){
    alarm(5);
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