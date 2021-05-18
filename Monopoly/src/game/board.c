#include <assert.h>
#include <stdlib.h>

#include <game/board.h>
#include <game/field.h>
#include <game/realty.h>
#include <util/input.h>
#include <util/arraylist.h>

Board* Board_new(char* filename) {
	Board* board = malloc(sizeof(Board));
	assert(board);

	for (int i = 0; i < BOARD_SIZE; ++i) {
		board->fields[i] = Field_new(FieldType_UNDEFINED, "NULL", NULL, Effect_notYetImplemented);
	}

	int realtyIndices[] = {1, 3, 6, 8, 9, 11, 13, 14, 16, 18, 19, 21, 23, 24, 26, 27, 29, 31, 32, 34, 37, 39};
	
	ArrayList* realties = parseCSV(filename);
	assert(realties->size == sizeof(realtyIndices) / sizeof(*realtyIndices));

	for (int i = 0; i < realties->size; ++i) {
		Realty* realty = *((Realty**)ArrayList_get(realties, i));
		Field_delete(board->fields[realtyIndices[i]]);
		board->fields[realtyIndices[i]] = Field_new(FieldType_REALTY, realty->name, realty, Effect_realty);
	}

	ArrayList_delete(realties);

	return board;
}

void Board_delete(Board* board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		Field_delete(board->fields[i]);
	}
	free(board);
}

void (*fieldPrintFunction[2])(Field* field) = {
	Field_printOwnedStatus,
	Field_printOwner
};

void Board_print(Board* board, const BoardPrintMode printMode) {
	void (*Field_print)(Field * field) = fieldPrintFunction[(int)printMode];

	int offset = BOARD_SIZE / 2;
	for (int i = 0; i < 1 + (BOARD_SIZE / 4); ++i) {
		Field_print(board->fields[offset + i]);
	}
	printf("\n");
	int whitespaces = (BOARD_SIZE / 4) - 1;
	int offset1 = offset - 1;
	int offset2 = offset + (BOARD_SIZE / 4) + 1;
	for (int i = 0; i < whitespaces; ++i) {
		Field_print(board->fields[offset1 - i]);
		for (int j = 0; j < whitespaces; ++j) {
			printf(" ");
		}
		Field_print(board->fields[offset2 + i]);
		printf("\n");
	}

	offset = (BOARD_SIZE / 4);
	for (int i = 0; i < 1 + (BOARD_SIZE / 4); ++i) {
		Field_print(board->fields[offset - i]);
	}
	printf("\n");
}

void Board_printForPlayer(Board* board, Player* player) {
	int offset = BOARD_SIZE / 2;
	for (int i = 0; i < 1 + (BOARD_SIZE / 4); ++i) {
		Player_printOnBoard(player, offset + i);
	}
	printf("\n");
	int whitespaces = (BOARD_SIZE / 4) - 1;
	int offset1 = offset - 1;
	int offset2 = offset + (BOARD_SIZE / 4) + 1;
	for (int i = 0; i < whitespaces; ++i) {
		Player_printOnBoard(player, offset1 - i);
		for (int j = 0; j < whitespaces; ++j) {
			printf(" ");
		}
		Player_printOnBoard(player, offset2 + i);
		printf("\n");
	}

	offset = (BOARD_SIZE / 4);
	for (int i = 0; i < 1 + (BOARD_SIZE / 4); ++i) {
		Player_printOnBoard(player, offset - i);
	}
	printf("\n");
	
}
