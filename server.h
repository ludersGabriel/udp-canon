/* --------------------------------------------------------------------------------------
 Headers e structs do servidor de um sistema de comunicacao via sockets UDP
   Objetivo: detectar a taxa de perda de pacotes em uma rede
   Restricoes: rodar cliente após servidor

   Autores: Eduardo Vudala e Gabriel Lüders
   Disciplina: Redes II
   Data da ultima atualizacao: 2023/2
----------------------------------------------------------------------------------------*/

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

#define MAXHOSTNAME 30

typedef struct REPORT_INFO {
  // <clientPid, <receivedId, Message>>
  map<int, vector<pair<int, Message>>> infos;

  // <clientPid, <expectedSeqNum for that PID>>
  map<int, int> expectedSeqNum;
} ReportInfo;

typedef struct SERVER {
  int sockDescr;

  // buffer to store the message being treated
  Message msg; 

  struct sockaddr_in serverAddress;

  // address of client to whom the server 
  // needs to respond to
  struct sockaddr_in clientAddress;

  struct hostent* hostInfo;
  char hostname[MAXHOSTNAME];

  FILE* output;
  
  int totalClientsTalking = 0;

  // totalMessagesExpected per clients 
  // not all of the messages expected
  int totalMessagesExpected = 0;
  int totalLostMessages = 0;
  int totalOutOfOrderMessages = 0;
  ReportInfo* reportInfo;

  // pointer to the variable that indicates if the 
  // alarm that controls the server timeout has been triggered
  bool* isDone;
} Server;

// used to create a server
Server* serverConstructor(char* port, bool& isDone, FILE* output);

// used to destroy a server
void serverDestructor(Server* server);

// used to receive a message from a client
void receiveFromClient(Server* server);

// used to send a message to a client
void sendToClient(Server* server);

// used to print the report of the server
void printReport(Server* server);

// writes the received info of each client to a file
void writeReceivedFile(Server* server);

// prints the lossReport to the output file
void printLossReport(Server* server);

// appends information about the current communication
// to the general report that is used to generate the 
// graphs
void appendGeneralReport(Server* server);

// verifies if the messages were received in order
// and prints the result to the output file
void verifyOrder(Server* server);

// prints information about how many messages were received
// how many were expected and lost etc
void printFooter(Server* server);

#endif