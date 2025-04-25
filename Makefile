# Simple Raylib Makefil# Simple Raylib Makefile with Root Header Inclusion

# 1. List your main source files here (space separated)
SRC = main.c algorithms/algorithms.c pixelBuffer/pixelBuffer.c input-handling/handlers.c input-handling/handle-input.c utils/utils.c

# 2. Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -I.  # -I. adds root to include path
LDFLAGS = -lraylib -lm -lpthread -ldl
TARGET = game

# 3. Automatic build rules
all: run

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
