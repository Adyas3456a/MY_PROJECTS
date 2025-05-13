# Makefile for MP3 Tag Reader & Editor

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o viewmp3.o editmp3.o
TARGET = tagreader

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c viewmp3.h editmp3.h util.h
	$(CC) $(CFLAGS) -c main.c

viewmp3.o: viewmp3.c viewmp3.h util.h
	$(CC) $(CFLAGS) -c viewmp3.c

editmp3.o: editmp3.c editmp3.h util.h
	$(CC) $(CFLAGS) -c editmp3.c

# Clean up
clean:
	rm -f *.o $(TARGET)
