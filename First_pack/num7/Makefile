CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BIN_DIR = bin

# Основные исходные файлы
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/Validation.c $(SRC_DIR)/Utils.c $(SRC_DIR)/Conversion.c $(SRC_DIR)/FileProcessing.c

# Тестовые исходные файлы
TEST_SOURCES = $(TEST_DIR)/test.c $(SRC_DIR)/Validation.c $(SRC_DIR)/Utils.c $(SRC_DIR)/Conversion.c $(SRC_DIR)/FileProcessing.c

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