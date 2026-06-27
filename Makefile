CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lraylib -lm

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
TEST_DRAW = tests/test_draw
TEST_PLATFORM = tests/test_platform
TEST_EMULATOR = tests/test_emulator
TEST_TIMERS = tests/test_timers
TEST_OPCODES = tests/test_opcodes

test: test-draw test-platform test-emulator test-timers test-opcodes

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

test-draw: $(TEST_DRAW)
	./$(TEST_DRAW)

test-platform: $(TEST_PLATFORM)
	./$(TEST_PLATFORM)

$(TEST_DRAW): tests/test_draw.c src/chip8.c src/display.c src/opcode.c src/stack.c
	$(CC) $(CFLAGS) tests/test_draw.c src/chip8.c src/display.c src/opcode.c src/stack.c -o $(TEST_DRAW)

test-emulator: $(TEST_EMULATOR)
	./$(TEST_EMULATOR)

test-timers: $(TEST_TIMERS)
	./$(TEST_TIMERS)

test-opcodes: $(TEST_OPCODES)
	./$(TEST_OPCODES)

$(TEST_OPCODES): tests/test_opcodes.c src/chip8.c src/display.c src/opcode.c src/stack.c
	$(CC) $(CFLAGS) tests/test_opcodes.c src/chip8.c src/display.c src/opcode.c src/stack.c -o $(TEST_OPCODES)

$(TEST_TIMERS): tests/test_timers.c src/chip8.c src/display.c src/opcode.c src/stack.c
	$(CC) $(CFLAGS) tests/test_timers.c src/chip8.c src/display.c src/opcode.c src/stack.c -o $(TEST_TIMERS)

$(TEST_EMULATOR): tests/test_emulator.c src/chip8.c src/display.c src/memory.c src/opcode.c src/stack.c
	$(CC) $(CFLAGS) tests/test_emulator.c src/chip8.c src/display.c src/memory.c src/opcode.c src/stack.c -o $(TEST_EMULATOR)

$(TEST_PLATFORM): tests/test_platform.c src/chip8.c src/display.c src/opcode.c src/stack.c src/platform.c
	$(CC) $(CFLAGS) tests/test_platform.c src/chip8.c src/display.c src/opcode.c src/stack.c src/platform.c -o $(TEST_PLATFORM) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_DRAW) $(TEST_PLATFORM) $(TEST_EMULATOR) $(TEST_TIMERS) $(TEST_OPCODES)

.PHONY: all run clean test-draw test-platform test-emulator test-timers test-opcodes test

