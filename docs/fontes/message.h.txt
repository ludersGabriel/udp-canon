/* --------------------------------------------------------------------------------------
 Headers e structs do tipo de mensagem utilizado no sistema de comunicacao via sockets UDP implementado
   Objetivo: detectar a taxa de perda de pacotes em uma rede
   Restricoes: rodar cliente após servidor

   Autores: Eduardo Vudala e Gabriel Lüders
   Disciplina: Redes II
   Data da ultima atualizacao: 2023/2
----------------------------------------------------------------------------------------*/

#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct MESSAGE {
    char message[100]; // buffer to store the message
    int messageId;
    int clientPid;
} Message;

// used to create a message
Message* messageConstructor(char* msg, int id, int pid);

// used to destroy a message
void messageDestructor(Message* message);

#endif