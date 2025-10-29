CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -O2
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.c 
MAIN_BIN = $(BIN_DIR)/main

all: $(MAIN_BIN)

$(MAIN_BIN): $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SOURCES) -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
