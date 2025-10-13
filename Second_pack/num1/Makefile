CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -O2
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/finite.c
TEST_SOURCES = $(TEST_DIR)/test.c $(SRC_DIR)/finite.c

MAIN_BIN = $(BIN_DIR)/main
TEST_BIN = $(BIN_DIR)/test

LIBS = -lm

all: $(MAIN_BIN) $(TEST_BIN)

$(MAIN_BIN): $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SOURCES) -o $@ $(LIBS)

$(TEST_BIN): $(TEST_SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_SOURCES) -o $@ $(LIBS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

test: $(TEST_BIN)
	./$(TEST_BIN)

.PHONY: all clean test
