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

typedef struct REPORT_INFO {
  map<int, vector<pair<int, Message>>> infos;
  map<int, int> expectedSeqNum;
} ReportInfo;

typedef struct SERVER {
  int sockDescr;
  Message msg;

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  struct hostent* hostInfo;
  char hostname[MAXHOSTNAME];
  bool silent;

  int totalClientsTalking = 0;
  int totalMessagesExpected = 0;
  int totalLostMessages = 0;
  int totalOutOfOrderMessages = 0;
  ReportInfo* reportInfo;
  bool* isDone;
} Server;

Server* serverConstructor(char* port, bool& isDone, bool silent);
void serverDestructor(Server* server);
void receiveFromClient(Server* server);
void sendToClient(Server* server);
void printReport(Server* server);
void writeReceivedFile(Server* server);
void printLossReport(Server* server);
void appendTotalMessagesToLost(Server* server);
void appendGeneralReport(Server* server);
void verifyOrder(Server* server);
void printFooter(Server* server);

#endif