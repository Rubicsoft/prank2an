# WARNING : Windows-compatible only
# 'w64devkit' is required and desireable to compile using this makefile

CC := g++
CFLAGS := -Wall -Wextra -O2
WINFLAG := -mwindows

SOURCE_DIR := Source

# Path to Raylib directories
RAYLIB_INCLUDE := raylib-5.5_win64_mingw-w64/include
RAYLIB_LIB := raylib-5.5_win64_mingw-w64/lib

# NOTE : Linking flags are always the last
LINK_FLAGS := -lraylib -lgdi32 -lwinmm

BUILD_DIR := Build
OUT := Flappy\ Bird\ Game.exe


all:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) \
	-o $(BUILD_DIR)/$(OUT) \
	-I $(RAYLIB_INCLUDE) -L $(RAYLIB_LIB) \
	$(SOURCE_DIR)/*.cpp \
	$(LINK_FLAGS) \
	$(WINFLAG)

clean:
	rm -rf $(BUILD_DIR)/$(OUT)

