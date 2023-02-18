#include <iostream>
#include <bits/stdc++.h>
#include <signal.h>

#include "server.h"
#include "message.h"

using namespace std;

bool isDone = false;

void resolveTimer(int signum){
  isDone = true;
}

int main() {
  Server* server = serverConstructor((char*)"8080", isDone);

  struct sigaction action;
  action.sa_handler = resolveTimer;
  sigemptyset (&action.sa_mask) ;
  action.sa_flags = 0 ;
  sigaction (SIGALRM, &action, 0);

  for(;!isDone;){
    alarm(5);
    receiveFromClient(server);
    alarm(0);
    sendToClient(server);
  }

  printReport(server);
  serverDestructor(server);
  writeReceivedFile(server);

  return 0;
}