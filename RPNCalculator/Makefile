CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lm

SRC_DIR = src
LIB_DIR = lib
INCLUDE_DIR = include
OBJ_DIR = obj
BUILD_DIR = build

MAIN_SRC = $(SRC_DIR)/graph.c
LIB_SRC = $(wildcard $(LIB_DIR)/*.c)

OBJ = $(patsubst $(LIB_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC)) \
      $(OBJ_DIR)/graph.o

TARGET = $(BUILD_DIR)/graph_app

all: create_dirs $(TARGET)

create_dirs:
	@mkdir -p $(OBJ_DIR) $(BUILD_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/graph.o: $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all create_dirs clean