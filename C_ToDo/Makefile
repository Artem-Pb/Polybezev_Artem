CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -I.
LDFLAGS := -lm

SRC_DIR := src
OBJ_DIR := $(SRC_DIR)/obj
BUILD_DIR := build
TARGET := $(BUILD_DIR)/todo_app

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
HEADERS := $(wildcard *.h)

ifeq ($(mode), release)
    CFLAGS += -O2
else
    CFLAGS += -g -O0
endif

all: prepare $(TARGET)

prepare:
	@mkdir -p $(OBJ_DIR) $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "✅ Собрано: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "🧹 Очищено!"

rebuild: clean all

.PHONY: all prepare clean rebuild