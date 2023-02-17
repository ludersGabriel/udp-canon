#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "message.h"

Message* messageConstructor(char* msg, int id, int pid) {
  if(strlen(msg) > 30) {
    printf("message: message too long\n");
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
  printf("message: %s\n", message->message);
  printf("messageId: %d\n", message->messageId);
  printf("clientPid: %d\n", message->clientPid);
}