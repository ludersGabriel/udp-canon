#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct MESSAGE {
    char message[100];
    int messageId;
    int clientPid;
} Message;

Message* messageConstructor(char* msg, int id, int pid);
void messageDestructor(Message* message);
void printMessage(Message* message);

#endif