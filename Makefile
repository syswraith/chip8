CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lraylib

# Added backslashes (\) to correctly chain the files together
SRC = \
	src/main.c \
	src/chip8.c \
	src/memory.c \
	src/stack.c \
	src/display.c \
	src/opcode.c \
	src/platform.c

TARGET = chip8

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean

