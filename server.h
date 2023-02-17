#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>
#include <bits/stdc++.h>
#include "message.h"

using namespace std;

#define QUEUESIZE 5
#define MAXHOSTNAME 30

typedef struct SERVER {
  int listenSocket;
  Message msg;

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  struct hostent* hostInfo;
  char hostname[MAXHOSTNAME];
  bool isUDP;

  vector<pair<int, int>> seq;
  int expectedSeqNum = 0;

} Server;

Server* serverConstructor(char* port, bool udp = true);
void serverDestructor(Server* server);
void receiveFromClient(Server* server);
void sendToClient(Server* server);
void printReport(Server* server);

#endif