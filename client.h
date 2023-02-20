#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// tudo que tem a ver com internet - Elias
#include <netinet/in.h>
#include <netdb.h> // sistema DNS
#include "message.h"

#include <bits/stdc++.h>

using namespace std;

typedef struct CLIENT {
    int socketDescriptor;
    struct sockaddr_in address;
    struct hostent *hp;
    char *host;
} Client; 


Client* clientConstructor(char* svName, char* port);
void clientDestructor(Client* client);
void sendToServer(Client* client, Message* msg);
void parentMain(vector<int> pids, bool silent = false);
void childMain(int balls, char* server, char* port, bool silent = false);
void handshake(
    char* server, 
    char* port, 
    char* clients, 
    char* cannonbals, 
    bool silent = false
);

#endif