# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Target binary
TARGET = lexical_analyser

# Source files
SRC = main.c lexer.c

# Header files
HEADERS = lexer.h

# Default rule
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean rule to remove the binary
clean:
	rm -f $(TARGET)
