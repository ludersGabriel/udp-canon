
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "client.h"

Client* clientConstructor(char* svName, char* port, bool udp) {
  Client *client = (Client*) malloc(sizeof(Client));

  client->host = svName;
  client->hp = gethostbyname(client->host);
  if(!client->hp){
    printf( "client: host %s not found\n", client->host);
    exit(1);
  }

  bcopy(
    (char*) client->hp->h_addr, 
    (char*) &(client->address.sin_addr), 
    client->hp->h_length
  );
  client->address.sin_family = client->hp->h_addrtype;

  client->address.sin_port = htons(atoi(port));

  int type = udp ? SOCK_DGRAM : SOCK_STREAM;
  client->socketDescriptor = socket(client->hp->h_addrtype, type, 0);
  if(client->socketDescriptor < 0){
    printf( "client: not able to open socket");
    exit(1);
  }

  return client;
}

void clientDestructor(Client* client) {
  close(client->socketDescriptor);
  free(client);
}

void sendToServer(Client* client, Message* msg) {

  int ret = sendto(
    client->socketDescriptor,
    msg,
    sizeof(Message),
    0,
    (struct sockaddr*) &(client->address),
    sizeof(client->address)
  );

  if(ret != sizeof(Message)){
    printf("client: couldn't send whole message\n");
    exit(1);
  }
}

void parentMain(vector<int> pids) {
  printf("client: forked all clients\n");

  int status = 0;
  int wpid;
  while ((wpid = wait(&status)) > 0);
  printf("\nclient: printing reports for each fork\n");

  // print reports here
  for(long unsigned int i = 0; i < pids.size(); i++){
    cout << endl;
    string fileName = "client" + to_string(pids[i]) + ".txt";
    ifstream file(fileName);
    string line;
    while(getline(file, line)){
      cout << line << endl;
    }
    file.close();
    remove(fileName.c_str());
  }

  int totalMessages = 0;
  printf("\nclient: printing sent report\n\n");
  for(auto i : pids){
    string sentReportName = "client" + to_string(i) + "SentReport.txt";
    ifstream sentReport(sentReportName);

    string line;
    int count = 1;
    while(getline(sentReport, line)){
      cout << line << endl;

      if(count == 3){
        int num = atoi(line.substr(line.find(':') + 2, line.length() - line.find(':')).c_str());
        totalMessages += num;
        count = 0;
      }

      count++;
    }
    cout << endl;
    
    sentReport.close();
    remove(sentReportName.c_str());
  }

  printf("client: sent %d messages\n\n", totalMessages);
}

void childMain(int balls, char* server, char* port){
  int cannonballs = balls;
  int myPid = getpid();

  Client* client = clientConstructor(server, port);
  vector<string> messages;

  string fileName = "client" + to_string(myPid) + ".txt";
  ofstream file(fileName);
  
  string sentReportName = "client" + to_string(myPid) + "SentReport.txt";
  ofstream sentReport(sentReportName, ios::app);

  file << "\tClient " << myPid << endl;

  int i;
  for(i = 1; i <= cannonballs; i++){
    char text[150];
    sprintf(text, "cannonball %d", i);
    Message* msg = messageConstructor(text, i, myPid);

    sendToServer(client, msg);
    sprintf(text, "\t\tsentId %d: sent %s\n", i, msg->message);
    file << text;

    messages.push_back(text);
    messageDestructor(msg);
  }
  
  sentReport << "\tClient " << myPid << endl;
  sentReport << "\t\tExpected to send: " << cannonballs << endl;
  sentReport << "\t\tMessages sent: " << i - 1 << endl;

  clientDestructor(client);
  file.close();
  sentReport.close();
}

void handshake(char* server, char* port, char* clients, char* cannonbals) {
  Client* client = clientConstructor(server, port);

  char text[80];
  sprintf(
    text, 
    "expected %d cannonballs from %d clients each", 
    atoi(cannonbals), 
    atoi(clients)
  );
  printf("client: %s\n", text);
  Message* msg = messageConstructor(text, atoi(cannonbals), atoi(clients));
  sendToServer(client, msg);

  clientDestructor(client);
}