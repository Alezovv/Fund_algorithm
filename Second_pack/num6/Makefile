# Компилятор и флаги
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Iinclude

# Папки
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Файлы
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/Student.c \
       $(SRC_DIR)/Utils.c \
       $(SRC_DIR)/Validation.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/main

# Правило по умолчанию
all: dirs $(TARGET)

# Линковка основной программы
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Компиляция отдельных .c файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Создание необходимых директорий
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Создание тестовых файлов
make_files:
	@echo "Создание input.txt и output.txt..."
	@touch input.txt output.txt

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) test_output.txt

# Пересборка
re: clean all

# Удобный запуск приложения
run: all
	@./$(TARGET)

# Цель для сборки и запуска тестов
test: dirs
	$(CC) $(CFLAGS) $(TEST_DIR)/tests.c \
	      $(SRC_DIR)/Student.c $(SRC_DIR)/Utils.c $(SRC_DIR)/Validation.c \
	      -o $(BIN_DIR)/test
	@./$(BIN_DIR)/test

.PHONY: all clean re run dirs make_files test
