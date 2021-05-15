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
		board->fields[i] = Field_new("NULL", NULL, Effect_notYetImplemented);
	}

	int realtyIndices[] = {1, 3, 6, 8, 9, 11, 13, 14, 16, 18, 19, 21, 23, 24, 26, 27, 29, 31, 32, 34, 37, 39};
	
	ArrayList* realties = parseCSV(filename);
	assert(realties->size == sizeof(realtyIndices) / sizeof(*realtyIndices));

	for (int i = 0; i < realties->size; ++i) {
		Realty* realty = *((Realty**)ArrayList_get(realties, i));
		Field_delete(board->fields[realtyIndices[i]]);
		board->fields[realtyIndices[i]] = Field_new(realty->name, realty, Effect_realty);
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