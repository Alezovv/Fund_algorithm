CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
SRC_DIR = src
BIN_DIR = bin

# Исходники
SOURCES = $(SRC_DIR)/main.c

# Цель по умолчанию
all: $(BIN_DIR)/main

# Компиляция тестового бинарника
$(BIN_DIR)/main: $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

# Создание папки bin, если её нет
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Очистка скомпилированных файлов
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean test
