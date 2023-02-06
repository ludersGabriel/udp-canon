#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// tudo que tem a ver com internet - Elias
#include <netinet/in.h>
#include <netdb.h> // sistema DNS

typedef struct CLIENT {
    int socketDescriptor;
    int numb;
    struct sockaddr_in address;
    struct hostent *hp;
    char buffer[BUFSIZ + 1];
    char *host;
    bool isUDP;
} Client; 

Client* clientConstructor(char* svName, char* port, bool udp = true);
void clientDestructor(Client* client);
void sendToServer(Client* client, char* message);
void waitForServer(Client* client);