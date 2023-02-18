#include "server.h"
#include "message.h"

Server* serverConstructor(char* port, bool& isDone){
  Server* server = (Server*) malloc(sizeof(Server));

  gethostname(server->hostname, MAXHOSTNAME);

  server->hostInfo = gethostbyname(server->hostname);
  if(!server->hostInfo){
    printf( "Server: couldn't get my IP\n");
    exit(1);
  }

  server->serverAddress.sin_port = htons(atoi(port));
  bcopy(
    (char*) server->hostInfo->h_addr,
    (char*) &(server->serverAddress.sin_addr),
    server->hostInfo->h_length
  );
  server->serverAddress.sin_family = server->hostInfo->h_addrtype;

  int type = SOCK_DGRAM;
  server->listenSocket = socket(server->hostInfo->h_addrtype, type, 0);
  if(server->listenSocket < 0){
    printf( "Server: couldn't open listen socket\n");
    exit(1);
  }

  int ret = bind(
    server->listenSocket,
    (struct sockaddr*) &(server->serverAddress),
    sizeof(server->serverAddress)
  );
  if(ret < 0){
    printf( "Server: couldn't bind to socket\n");
    exit(1);
  }

  server->reportInfo = new ReportInfo();
  server->isDone = &isDone;
  return server;
}

void serverDestructor(Server* server){
  close(server->listenSocket);
  free(server);
}

void receiveFromClient(Server* server){
  int i = sizeof(server->clientAddress);
  Message msg;

  recvfrom(
    server->listenSocket,
    &msg,
    sizeof(Message),
    0,
    (struct sockaddr*) &(server->clientAddress),
    (socklen_t*) &i
  );

  if(server->totalMessagesExpected == 0){
    server->totalMessagesExpected = msg.messageId;
    server->totalClientsTalking = msg.clientPid;
    printf( "server: %s\n", msg.message);
    return;
  }

  if(*(server->isDone)) return;

  if(!(server->reportInfo->expectedSeqNum.count(msg.clientPid))){
    server->reportInfo->expectedSeqNum[msg.clientPid] = 0;
  }

  server->reportInfo->infos[msg.clientPid].push_back(
    pair(
      ++(server->reportInfo->expectedSeqNum[msg.clientPid]),
      msg
    )
  );

}

void sendToClient(Server* server){
  sendto(
    server->listenSocket,
    &(server->msg),
    sizeof(Message),
    0,
    (struct sockaddr*) &(server->clientAddress),
    sizeof(server->clientAddress)
  );
}

void printReport(Server* server){
  printf("\nserver: printing report\n\n");
  for(auto it : server->reportInfo->infos){
    printf( "\tClient %d\n", it.first);
    for(auto it2 : it.second){
      printf( "\t\treceivedId %d: received %s\n", it2.first, it2.second.message);
    }
    printf("\n");
  }
}

void writeReceivedFile(Server* server){
  ofstream file("packets-received.csv");
  file << "clientId, amountReceived\n";

  for(auto it : server->reportInfo->infos){
    file << it.first << ", " << it.second.size() << endl;
  }
}

void printLossReport(Server* server){
  printf( "server: printing loss report\n\n");
  for(auto it : server->reportInfo->infos){
    printf( "\tClient %d\n", it.first);
    printf(
      "\t\tHow many packets received: %ld\n",
      it.second.size()
    );
    printf(
      "\t\tHow many packets expected: %d\n",
      server->totalMessagesExpected
    );
    int lost = server->totalMessagesExpected - it.second.size();
    printf(
      "\t\tHow many packets lost: %d\n\n", 
      lost
    );

    server->totalLostMessages += lost;
  }

  printf(
    "server: lost %d messages\n\n",
    server->totalLostMessages
  );
}