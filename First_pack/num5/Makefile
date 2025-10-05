CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic 
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/validations.c $(SRC_DIR)/flags.c
TEST_SOURCES = $(TEST_DIR)/test.c $(SRC_DIR)/validations.c $(SRC_DIR)/flags.c

all: $(BIN_DIR)/main $(BIN_DIR)/test

$(BIN_DIR)/main: $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SOURCES) -o $@

$(BIN_DIR)/test: $(TEST_SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_SOURCES) -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

test: $(BIN_DIR)/test
	./$(BIN_DIR)/test

.PHONY: all clean test