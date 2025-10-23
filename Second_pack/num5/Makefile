# Компилятор и флаги
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Iinclude

# Папки
SRC_DIR = src
BIN_DIR = bin

SRC = $(SRC_DIR)/main.c
TARGET = $(BIN_DIR)/justify

# Правило по умолчанию
all: dirs $(TARGET)

# Компиляция и линковка
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

# Создание необходимых директорий
dirs:
	mkdir -p $(BIN_DIR)

# Очистка
clean:
	rm -rf $(BIN_DIR) output.txt

# Пересборка
re: clean all

# Удобный запуск
run: all
	@./$(TARGET)

# Тест с input.txt и проверкой
test: all
	@echo "=== Running test ==="
	@./$(TARGET) < input.txt
	@echo "Done. Check output in output.txt"

.PHONY: all clean re run test dirs
