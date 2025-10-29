# === Настройки проекта ===
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -Iinclude

# === Каталоги ===
SRC_DIR := src
OBJ_DIR := object
BIN_DIR := bin
TEST_DIR := tests

# === Исходники ===
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# === Основная программа ===
TARGET := $(BIN_DIR)/main

# === Тесты ===
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_BIN := $(BIN_DIR)/test
TEST_SRC_FULL := $(filter-out $(SRC_DIR)/main.c,$(SRC)) # все исходники кроме main.c

# === Основная цель ===
all: $(TARGET)

# === Компиляция основной программы ===
$(TARGET): $(OBJ) | $(BIN_DIR)
	@echo "🔧 Linking main..."
	$(CC) $(OBJ) -o $(TARGET)
	@echo "✅ Build complete: $(TARGET)"

# === Компиляция .c → .o ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "🧩 Compiling $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# === Сборка тестов ===
test: $(TEST_BIN)
	@echo "🚀 Running tests..."
	@./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(TEST_SRC_FULL) | $(BIN_DIR)
	@echo "🔧 Linking tests..."
	$(CC) $(CFLAGS) $(TEST_SRC) $(TEST_SRC_FULL) -o $(TEST_BIN)
	@echo "✅ Test build complete: $(TEST_BIN)"

# === Создание директорий при необходимости ===
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# === Очистка ===
clean:
	@echo "🧹 Cleaning..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# === Запуск основной программы ===
run: $(TARGET)
	@echo "🚀 Running program..."
	@./$(TARGET)

.PHONY: all clean run test
