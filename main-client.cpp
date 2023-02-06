#include "client.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Client* client = clientConstructor((char*)"vanaheim", (char*)"8080");
  sendToServer(client, (char*)"Hello World!");
  waitForServer(client);
  clientDestructor(client);

  return 0;
}