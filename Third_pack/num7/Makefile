CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -O2
LOG_FLAG = -DLOG_ON
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/Calculate.c $(SRC_DIR)/Dijkstra.c $(SRC_DIR)/Logging.c $(SRC_DIR)/Stack.c $(SRC_DIR)/StatusCode.c
MAIN_BIN = $(BIN_DIR)/main

all: $(MAIN_BIN)

$(MAIN_BIN): $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SOURCES) -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)


memcheck: $(TEST_BIN)
	@echo "=== Проверка памяти через AddressSanitizer ==="
	@./$(TEST_BIN)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean