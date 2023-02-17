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

typedef struct CLIENT {
    int socketDescriptor;
    int numb;
    struct sockaddr_in address;
    struct hostent *hp;
    char buffer[BUFSIZ + 1];
    char *host;
} Client; 


Client* clientConstructor(char* svName, char* port, bool udp = true);
void clientDestructor(Client* client);
void sendToServer(Client* client, Message* msg);

#endif