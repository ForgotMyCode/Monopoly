#pragma once
#include <stdio.h>

#include <game/field.h>

#define BOARD_SIZE 40

struct Board {
	struct Field* fields[BOARD_SIZE];
};

typedef struct Board Board;

struct Board* Board_new(char* filename);

void Board_delete(Board* board);
