#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "message.h"

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

void messageDestructor(Message* message) {
  free(message);
}

void printMessage(Message* message) {
  fprintf(stdout, "message: %s\n", message->message);
  fprintf(stdout, "messageId: %d\n", message->messageId);
  fprintf(stdout, "clientPid: %d\n", message->clientPid);
}