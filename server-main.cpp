#include "server.h"

int main() {
  Server* server = serverConstructor((char*)"8080");

  for(;;){
    receiveFromClient(server);
    sendToClient(server);
  }

  serverDestructor(server);

  return 0;
}