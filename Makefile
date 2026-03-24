CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = sort-visualizer
SRC_DIR = src
OBJ_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBS = -lncurses -lSDL2 -lSDL2_mixer -lm

SDL_CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_mixer 2>/dev/null)
SDL_LIBS   = $(shell pkg-config --libs   sdl2 SDL2_mixer 2>/dev/null || echo "-lSDL2 -lSDL2_mixer")

ALL_CFLAGS = $(CFLAGS) $(SDL_CFLAGS)
ALL_LIBS   = -lncurses $(SDL_LIBS) -lm

.PHONY: all clean run

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(ALL_CFLAGS) -o $@ $^ $(ALL_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(ALL_CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

install:
	bash utils/dependencies.sh