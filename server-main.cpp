#include "server.h"
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
  Server* server = serverConstructor((char*)"8080");

  for(;;){
    receiveFromClient(server);
    sendToClient(server);
    printReport(server);
  }

  serverDestructor(server);

  return 0;
}