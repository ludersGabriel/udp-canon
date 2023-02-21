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