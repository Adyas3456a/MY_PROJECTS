CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I.

CLIENT_SRC = tftp_client.c tftp.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
CLIENT_EXE = tftp_client

SERVER_SRC = tftp_server.c tftp.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
SERVER_EXE = tftp_server

.PHONY: all clean

all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_EXE): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o $(CLIENT_EXE) $(SERVER_EXE)
