#pragma once
#include <stdio.h>

#include <game/field.h>

#define BOARD_SIZE 40

typedef struct Board Board;

struct Board {
	struct Field* fields[BOARD_SIZE];
};

struct Board* Board_new(char* filename);

void Board_delete(Board* board);
