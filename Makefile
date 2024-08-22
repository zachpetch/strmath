CC=gcc

SRC_DIR = src
OBJ_DIR = obj

CFLAGS += -Wall -g

BIN=strmath
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

.phony: all clean

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(BIN) $(OBJECTS)
