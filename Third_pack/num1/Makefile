CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -O1 -fsanitize=address -g
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BIN_DIR = bin

# Основные исходники
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/Arr.c $(SRC_DIR)/ToBase.c
MAIN_BIN = $(BIN_DIR)/main

# Тестовые файлы
TEST_SRC = $(TEST_DIR)/test.c $(SRC_DIR)/Arr.c $(SRC_DIR)/ToBase.c
TEST_BIN = $(BIN_DIR)/test

# --- Основная программа ---
all: $(MAIN_BIN)

$(MAIN_BIN): $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SOURCES) -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# --- Тесты ---
test: $(TEST_BIN)
	@echo "=== Запуск тестов ==="
	@./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_SRC) -o $@

# --- Проверка утечек памяти ---
# Автоматически использует Valgrind, если установлен, иначе AddressSanitizer
memcheck: $(TEST_BIN)
	@echo "=== Проверка памяти через AddressSanitizer ==="
	@./$(TEST_BIN)

# --- Очистка ---
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean test memcheck
