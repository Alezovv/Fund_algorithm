CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -O2
LOG_FLAG = -DLOG_ON
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/Calculate.c $(SRC_DIR)/Dijkstra.c $(SRC_DIR)/Logging.c $(SRC_DIR)/Stack.c $(SRC_DIR)/StatusCode.c
MAIN_BIN = $(BIN_DIR)/main
TEST_SOURCES = $(TEST_DIR)/test.c
TEST_BIN = $(BIN_DIR)/test

# ==== Основная цель ====
all: $(MAIN_BIN)

# ==== Сборка основной программы ====
$(MAIN_BIN): $(SOURCES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SOURCES) -o $@

# ==== Сборка тестов ====
$(TEST_BIN): $(TEST_SOURCES) $(filter-out $(SRC_DIR)/main.c, $(SOURCES)) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(filter-out $(SRC_DIR)/main.c, $(SOURCES)) $(TEST_SOURCES) -o $@

# ==== Запуск основной программы ====
run: $(MAIN_BIN)
	@echo "=== Запуск программы ==="
	@./$(MAIN_BIN)

# ==== Запуск тестов ====
test: $(TEST_BIN)
	@echo "=== Запуск интеграционных тестов ==="
	@./$(TEST_BIN)

# ==== Проверка памяти (AddressSanitizer) ====
memcheck: $(TEST_BIN)
	@echo "=== Проверка памяти через AddressSanitizer ==="
	@ASAN_OPTIONS=detect_leaks=1 ./$(TEST_BIN)

# ==== Каталог для бинарников ====
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ==== Очистка ====
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean test memcheck run
