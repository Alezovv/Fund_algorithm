CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
SRC_DIR = src
BIN_DIR = bin
INC_DIR = include

# Исходники
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/function.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Цель по умолчанию
all: $(BIN_DIR)/main

# Компиляция основного бинарника
$(BIN_DIR)/main: $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Компиляция объектных файлов
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Создание папки bin, если её нет
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Очистка скомпилированных файлов
clean:
	rm -rf $(BIN_DIR)

# Перекомпиляция
rebuild: clean all

.PHONY: all clean rebuild