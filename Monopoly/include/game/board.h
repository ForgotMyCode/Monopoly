#pragma once
#include <stdio.h>

#include <core.h>
#include <game/field.h>

#define BOARD_SIZE 40

static const BoardPrintMode BoardPrintMode_OWNEDSTATUS = 0;
static const BoardPrintMode BoardPrintMode_OWNERS = 1;

struct Board {
	struct Field* fields[BOARD_SIZE];
};

struct Board* Board_new(char* filename);

void Board_delete(Board* board);

void Board_print(Board* field, const BoardPrintMode printMode);

void Board_printForPlayer(Board* board, struct Player* player);
