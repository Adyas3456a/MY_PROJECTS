CC = gcc
CFLAGS = -Wall -g
TARGET = msh
SRCS = msh.c
OBJS = $(SRCS:.c=.o)

# Add a variable for the files you want to remove
TXT_FILES = *.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files, target, and any .txt files created during runtime
clean:
	rm -f $(OBJS) $(TARGET) $(TXT_FILES)

.PHONY: all clean
