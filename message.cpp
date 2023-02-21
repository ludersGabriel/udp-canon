#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "message.h"

// used to create a message
Message* messageConstructor(char* msg, int id, int pid) {
  if(strlen(msg) > 100) {
    fprintf(stdout, "message: message too long\n");
    return NULL;
  }

  Message *message = (Message*) malloc(sizeof(Message));
  strcpy(message->message, msg);
  message->messageId = id;
  message->clientPid = pid;

  return message;
}

// used to destroy a message
void messageDestructor(Message* message) {
  free(message);
}