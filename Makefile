# /* --------------------------------------------------------------------------------------
#    Programa que implementa o cliente de um sistema de comunicacao via sockets UDP
#    Objetivo: detectar a taxa de perda de pacotes em uma rede
#    Restricoes: rodar cliente após servidor

#    Autores: Eduardo Vudala e Gabriel Lüders
#    Disciplina: Redes II
#    Data da ultima atualizacao: 2023/2
# ----------------------------------------------------------------------------------------*/

# ----------------------------------------------------------------- #
# Declaration of targets and compiling options
CFLAGS = -Wall -g -std=c++17
CC = g++
LIBS = -lstdc++fs 
OBJ_SERVER = server-main.o message.o server.o
OBJ_CLIENT = main-client.o message.o client.o
EXEC_SERVER = ./server
EXEC_CLIENT = ./client

# ----------------------------------------------------------------- #
# Compilation directives
all: ${EXEC_SERVER} ${EXEC_CLIENT}

${EXEC_SERVER}: $(OBJ_SERVER)
	$(CC) -o ${EXEC_SERVER} $(OBJ_SERVER) $(LIBS)

${EXEC_CLIENT}: $(OBJ_CLIENT)
	$(CC) -o ${EXEC_CLIENT} $(OBJ_CLIENT) $(LIBS)

server-main.o: server-main.cpp 
	$(CC) -c server-main.cpp $(CFLAGS) $(LIBS)

main-client.o: main-client.cpp
	$(CC) -c main-client.cpp $(CFLAGS) $(LIBS)

client.o: client.cpp client.h
	$(CC) -c client.cpp $(CFLAGS)

server.o: server.cpp server.h
	$(CC) -c server.cpp $(CFLAGS)

message.o: message.cpp message.h
	$(CC) -c message.cpp $(CFLAGS)

runServer: all
	${EXEC_SERVER}

runClient: all
	${EXEC_CLIENT}

# ----------------------------------------------------------------- #
# Cleaning directives
clean:
	$(RM) *.o *.gch

purge: clean
	$(RM) ${EXEC_CLIENT} ${EXEC_SERVER} 