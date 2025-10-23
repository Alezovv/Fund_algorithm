CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
SRC_DIR = src
BIN_DIR = bin
INC_DIR = include
TEST_DIR = tests

# Исходники
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/function.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Исходники для тестов
TEST_SOURCES = $(TEST_DIR)/test.c $(SRC_DIR)/function.c
TEST_BINARY = $(BIN_DIR)/test

# Цель по умолчанию
all: $(BIN_DIR)/main

# Основной бинарник
$(BIN_DIR)/main: $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Объектные файлы
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Создание папки bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Сборка тестов
test: $(TEST_BINARY)
	@echo "Running tests..."
	@./$(TEST_BINARY)

$(TEST_BINARY): $(TEST_SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(TEST_SOURCES) -o $@

# Очистка
clean:
	rm -rf $(BIN_DIR)

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild test
