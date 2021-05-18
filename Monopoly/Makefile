TARGET_EXEC := out

BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*.c)

CFLAGS := -I./include -O0

CC := gcc

out: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET_EXEC)