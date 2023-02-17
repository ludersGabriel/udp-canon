#include <iostream>
#include <bits/stdc++.h>
#include "server.h"
#include "message.h"

using namespace std;

int main() {
  Server* server = serverConstructor((char*)"8080");

  for(;;){
    receiveFromClient(server);
    sendToClient(server);
  }

  serverDestructor(server);

  return 0;
}