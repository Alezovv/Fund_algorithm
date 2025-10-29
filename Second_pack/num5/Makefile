# === Компилятор и флаги ===
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Iinclude

# === Папки ===
SRC_DIR = src
BIN_DIR = bin

# === Файлы ===
SRC = $(wildcard $(SRC_DIR)/*.c)
TARGET = $(BIN_DIR)/justify

# === Правило по умолчанию ===
all: dirs $(TARGET)

# === Компиляция и линковка ===
$(TARGET): $(SRC)
	@echo "🔧 Building..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "✅ Build complete: $(TARGET)"

# === Создание необходимых директорий ===
dirs:
	mkdir -p $(BIN_DIR)

# === Очистка ===
clean:
	@echo "🧹 Cleaning..."
	rm -rf $(BIN_DIR) output.txt

# === Пересборка ===
re: clean all

# === Удобный запуск программы ===
run: all
	@echo "🚀 Running..."
	@./$(TARGET)

# === Тест с input.txt ===
test: all
	@echo "=== Running test ==="
	@./$(TARGET) < input.txt > output.txt
	@echo "✅ Done. Check output.txt"

.PHONY: all clean re run test dirs
