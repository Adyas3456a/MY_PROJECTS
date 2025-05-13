# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Source files (use renamed fixed files)
SRCS = s2html_main.c s2html_conv.c s2html_event.c

# Output executable
TARGET = source_to_html

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Clean generated files
clean:
	rm -f $(TARGET) *.o *.html

# Run with sample test file
run:
	./$(TARGET) test.c output.html
	@echo "Opening HTML output in browser..."
	open output.html

# Run with line numbers
run-n:
	./$(TARGET) test.c output.html -n
	@echo "Opening HTML output in browser..."
	open output.html
