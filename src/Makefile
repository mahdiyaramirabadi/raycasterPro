# ---------- Compiler ----------
CC = gcc

# ---------- Project ----------
TARGET = app
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

# ---------- Find all .c files ----------
SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ---------- Homebrew ----------
BREW_PREFIX := $(shell brew --prefix)

# ---------- Flags ----------
CFLAGS  = -Wall -Wextra -std=c11 \
          -I$(INC_DIR) \
          -I$(BREW_PREFIX)/include

LDFLAGS = -L$(BREW_PREFIX)/lib \
          -lraylib \
          -framework OpenGL \
          -framework Cocoa \
          -framework IOKit \
          -framework CoreVideo

# ---------- Rules ----------
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
