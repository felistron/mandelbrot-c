CC = gcc
CFLAGS = -Wall -g

APP_NAME = mandelbrot
ENTRY_FILE = main
SOURCE_DIR = src
OUTPUT_DIR = build

INCLUDE_DIR = include
EXTERNAL_INCLUDE_DIR = external/include
EXTERNAL_LIB_DIR = external/lib
LIBS = -lraylib/raylib

build: $(SOURCE_DIR)/$(ENTRY_FILE).c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/$(ENTRY_FILE).c -o $(OUTPUT_DIR)/$(APP_NAME).exe -I$(INCLUDE_DIR) -I$(EXTERNAL_INCLUDE_DIR) -L$(EXTERNAL_LIB_DIR) $(LIBS)

run: $(OUTPUT_DIR)/$(APP_NAME).exe
	./$(OUTPUT_DIR)/$(APP_NAME).exe
