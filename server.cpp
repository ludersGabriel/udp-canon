#include "server.h"
#include "message.h"

Server* serverConstructor(char* port, bool& isDone, FILE* output){
  Server* server = (Server*) malloc(sizeof(Server));

  server->output = output;

  gethostname(server->hostname, MAXHOSTNAME);

  server->hostInfo = gethostbyname(server->hostname);
  if(!server->hostInfo){
    fprintf(stdout,  "Server: couldn't get my IP\n");
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
  server->sockDescr = socket(server->hostInfo->h_addrtype, type, 0);
  if(server->sockDescr < 0){
    fprintf(stdout,  "Server: couldn't open listen socket\n");
    exit(1);
  }

  int ret = bind(
    server->sockDescr,
    (struct sockaddr*) &(server->serverAddress),
    sizeof(server->serverAddress)
  );
  if(ret < 0){
    fprintf(stdout,  "Server: couldn't bind to socket\n");
    exit(1);
  }

  server->reportInfo = new ReportInfo();
  server->isDone = &isDone;
  return server;
}

void serverDestructor(Server* server){
  close(server->sockDescr);
  free(server);
}

void receiveFromClient(Server* server){
  int i = sizeof(server->clientAddress);

  recvfrom(
    server->sockDescr,
    &(server->msg),
    sizeof(Message),
    0,
    (struct sockaddr*) &(server->clientAddress),
    (socklen_t*) &i
  );

  if(server->totalMessagesExpected == 0){
    server->totalMessagesExpected = (server->msg).messageId;
    server->totalClientsTalking = (server->msg).clientPid;
    fprintf(server->output,  "server: %s\n", (server->msg).message);
    return;
  }

  if(*(server->isDone)) return;

  if(!(server->reportInfo->expectedSeqNum.count((server->msg).clientPid))){
    server->reportInfo->expectedSeqNum[(server->msg).clientPid] = 0;
  }

  server->reportInfo->infos[(server->msg).clientPid].push_back(
    pair(
      ++(server->reportInfo->expectedSeqNum[(server->msg).clientPid]),
      (server->msg)
    )
  );
}

void sendToClient(Server* server){
  sendto(
    server->sockDescr,
    &(server->msg),
    sizeof(Message),
    0,
    (struct sockaddr*) &(server->clientAddress),
    sizeof(server->clientAddress)
  );
}

void printReport(Server* server){
  fprintf(server->output, "\nserver: printing report\n\n");
  for(auto it : server->reportInfo->infos){
    fprintf(server->output,  "\tClient %d\n", it.first);
    for(auto it2 : it.second){
      fprintf(server->output,  "\t\treceivedId %d: received %s\n", it2.first, it2.second.message);
    }
    fprintf(server->output, "\n");
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
  fprintf(server->output,  "server: printing loss report\n\n");
  for(auto it : server->reportInfo->infos){
    int lost = server->totalMessagesExpected - it.second.size();
    server->totalLostMessages += lost;

    fprintf(server->output,  "\tClient %d\n", it.first);
    fprintf(server->output, 
      "\t\tHow many packets received: %ld\n",
      it.second.size()
    );
    fprintf(server->output, 
      "\t\tHow many packets expected: %d\n",
      server->totalMessagesExpected
    );
    fprintf(server->output, 
      "\t\tHow many packets lost: %d\n\n", 
      lost
    );
  }
}

void appendTotalMessagesToLost(Server* server){
  ofstream file("total-messages-to-lost.csv", ios::app);
  file << server->totalMessagesExpected * server->totalClientsTalking 
  << ", " << server->totalLostMessages << endl;

  file.close();
}

void appendGeneralReport(Server* server){
  ofstream file("general-report.csv", ios::app);
  float totalMessages = (float) server->totalMessagesExpected * server->totalClientsTalking;
  float totalLost = (float) server->totalLostMessages;
  float lossRate = totalLost / totalMessages * 100;
  file << server->totalClientsTalking << ", " 
  << totalMessages << ", " 
  << totalLost << ", "
  << lossRate << endl;

  file.close();
}

void verifyOrder(Server* server){
  fprintf(server->output, "server: out of order report\n\n");
  for(auto it : server->reportInfo->infos){
    int max = 0;
    vector<int> received;
    int clientId = it.first;

    bool printHeader = true;
    for(unsigned long int i = 0; i < it.second.size(); i++){
      auto it2 = it.second[i];

      int id = it2.second.messageId;
      if(id > max) max = id;
      else if(id < max){
        if(printHeader){
          fprintf(server->output, "\tClient %d\n", clientId);
          printHeader = false;
        }
        server->totalOutOfOrderMessages += 1;

        for(unsigned long int j = i - 2; j < i + 2; j++){
          if(j < 0 || j >= it.second.size()) continue;
          fprintf(server->output, 
            "\t\treceivedId = %d, cannonballId = %d\n", 
            it.second[j].first, 
            it.second[j].second.messageId
          );
        }
      }
    }
  }
}

void printFooter(Server* server){
  float totalMessages = (float) server->totalMessagesExpected * server->totalClientsTalking;
  fprintf(server->output, 
    "server: total of %0.2f messages expected\n",
    totalMessages
  );

  fprintf(server->output, 
    "server: lost %d messages\n", 
    server->totalLostMessages
  );

  fprintf(server->output, 
    "server: packet loss rate of %0.2f%%\n",
    (float) server->totalLostMessages / totalMessages * 100
  );

  fprintf(server->output, 
    "server: received %d messages out of order\n\n", 
    server->totalOutOfOrderMessages
  );
}