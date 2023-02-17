#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <fstream> 

#include "client.h"
#include "message.h"

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  if(argc != 5) {
    printf("Usage: client <server> <port> <clients> <cannonballs>\n");
    exit(1);
  }

  int pid = 0;
  int clients = atoi(argv[3]);
  vector<int> pids;
  do {
    pid = fork();
    pids.push_back(pid);
  }while(pid && --clients);

  if(pid) {
    printf("client: forked all cannonballs\n");

    int status = 0;
    int wpid;
    while ((wpid = wait(&status)) > 0);
    printf("client: printing reports for each fork\n");

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
    }
    cout << endl;
    return 0;
  }

  int cannonballs = atoi(argv[4]);
  int myPid = getpid();

  Client* client = clientConstructor((char*)argv[1], (char*)argv[2]);
  vector<string> messages;

  string fileName = "client" + to_string(myPid) + ".txt";
  ofstream file(fileName);

  file << "\tClient " << myPid << endl;

  for(int i = 1; i <= cannonballs; i++){
    char text[50];
    sprintf(text, "cannonball %d", i);
    Message* msg = messageConstructor(text, i, myPid);

    sendToServer(client, msg);
    sprintf(text, "\t\t%d: sent %s\n", i, msg->message);
    file << text;

    messages.push_back(text);
    messageDestructor(msg);
  }
  
  clientDestructor(client);
  file.close();

  return 0;
}