/* --------------------------------------------------------------------------------------
  Biblioteca do tipo de mensagem utilizado no sistema de comunicacao via sockets UDP implementado
   Objetivo: detectar a taxa de perda de pacotes em uma rede
   Restricoes: rodar cliente após servidor

   Autores: Eduardo Vudala e Gabriel Lüders
   Disciplina: Redes II
   Data da ultima atualizacao: 2023/2
----------------------------------------------------------------------------------------*/

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