# mac, sdl2 genom homebrew, gcc genom homebrew
SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = play
#INCLUDE_PATHS = -Iinclude -Iinclude/SDL2/ -Iinclude/SDL2_image/ -Iinclude/SDL2_mixer/ -Iinclude/SDL2_ttf/
INCLUDE_PATHS = -Iinclude -I/usr/local/include/SDL2
#LIBRARY_PATHS = -Llib -Llib/SDL2_image/ -Llib/SDL2_mixer/ -Llib/SDL2_ttf/
LIBRARY_PATHS = -Llib -L/usr/local/lib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)