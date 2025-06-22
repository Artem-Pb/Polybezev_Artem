# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2
LDFLAGS =

# Директории
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Исходные файлы
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Имя исполняемого файла
TARGET = $(BIN_DIR)/todo_app

# Режим сборки (по умолчанию debug)
ifeq ($(mode),release)
    CFLAGS += $(RELEASE_FLAGS)
else
    CFLAGS += $(DEBUG_FLAGS)
endif

# Основная цель
all: prepare $(TARGET)

# Подготовка директорий
prepare:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Сборка завершена. Исполняемый файл: $(TARGET)"

# Правило для объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Очистка завершена"

# Пересборка
rebuild: clean all

# Установка (опционально)
install: $(TARGET)
	@cp $(TARGET) /usr/local/bin
	@echo "Приложение установлено в /usr/local/bin"

# Форматирование кода
format:
	clang-format -i $(SOURCES) $(HEADERS)
	@echo "Форматирование завершено"

# Справка
help:
	@echo "Использование:"
	@echo "  make           - сборка в режиме отладки"
	@echo "  make mode=release - сборка в релизном режиме"
	@echo "  make clean     - удаление собранных файлов"
	@echo "  make rebuild   - полная пересборка"
	@echo "  make install   - установка в систему"
	@echo "  make format    - форматирование кода"

.PHONY: all prepare clean rebuild install format help