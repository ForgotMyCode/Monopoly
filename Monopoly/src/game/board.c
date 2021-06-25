#include <assert.h>
#include <stdlib.h>

#include <game/board.h>
#include <game/field.h>
#include <game/realty.h>
#include <util/arraylist.h>
#include <util/input.h>
#include <util/mathutils.h>

const int jailIndex = 10;
const int colorCounts[] = {2, 3, 3, 3, 3, 3, 3, 2};

Board* Board_new(char* filename) {
	Board* board = malloc(sizeof(Board));
	assert(board);

	for (int i = 0; i < BOARD_SIZE; ++i) {
		board->fields[i] = Field_new(FieldType_UNDEFINED, "NULL", NULL, Effect_notYetImplemented);
	}

	int realtyIndices[] = {1, 3, 6, 8, 9, 11, 13, 14, 16, 18, 19, 21, 23, 24, 26, 27, 29, 31, 32, 34, 37, 39};
	int realtyColors[] =  {0, 0, 1, 1, 1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,  5,  5,  6,  6,  6,  7,  7};
	
	board->realties = parseCSV(filename);
	assert(board->realties->size == sizeof(realtyIndices) / sizeof(*realtyIndices));

	for (int i = 0; i < board->realties->size; ++i) {
		Realty* realty = *((Realty**)ArrayList_get(board->realties, i));
		realty->color = realtyColors[i];

		Field_delete(board->fields[realtyIndices[i]]);
		board->fields[realtyIndices[i]] = Field_new(FieldType_REALTY, realty->name, realty, Effect_realty);
	}

	int incomeTaxIndex = 4;
	Field_delete(board->fields[incomeTaxIndex]);
	board->fields[incomeTaxIndex] = Field_new(FieldType_TAX_INCOME, "INCOME TAX", NULL, Effect_Tax);

	int jailVisitIndex = 10;
	Field_delete(board->fields[jailVisitIndex]);
	board->fields[jailVisitIndex] = Field_new(FieldType_JAIL_VISIT, "VISIT JAIL", NULL, Effect_visitJail);

	int goToJailIndex = 30;
	Field_delete(board->fields[goToJailIndex]);
	board->fields[goToJailIndex] = Field_new(FieldType_JAIL_GOTO, "GO TO JAIL", NULL, Effect_goToJail);

	int luxuryTaxIndex = 38;
	Field_delete(board->fields[luxuryTaxIndex]);
	board->fields[luxuryTaxIndex] = Field_new(FieldType_TAX_LUXURY, "LUXURY TAX", NULL, Effect_Tax);

	int railIndex;
	char* railName;
	Rail* railroad;
	
	// rail 1
	railIndex = 5;
	railName = "Reading Railroad";
	railroad = Rail_new(railName);
	Field_delete(board->fields[railIndex]);
	board->fields[railIndex] = Field_new(FieldType_RAILROAD, railName, railroad, Effect_railroad);
	board->railroads[0] = railroad;

	// rail 2
	railIndex = 15;
	railName = "Pennsylvania Railroad";
	railroad = Rail_new(railName);
	Field_delete(board->fields[railIndex]);
	board->fields[railIndex] = Field_new(FieldType_RAILROAD, railName, railroad, Effect_railroad);
	board->railroads[1] = railroad;

	// rail 3
	railIndex = 25;
	railName = "B. & O. Railroad";
	railroad = Rail_new(railName);
	Field_delete(board->fields[railIndex]);
	board->fields[railIndex] = Field_new(FieldType_RAILROAD, railName, railroad, Effect_railroad);
	board->railroads[2] = railroad;

	// rail 4
	railIndex = 35;
	railName = "Short Line";
	railroad = Rail_new(railName);
	Field_delete(board->fields[railIndex]);
	board->fields[railIndex] = Field_new(FieldType_RAILROAD, railName, railroad, Effect_railroad);
	board->railroads[3] = railroad;

	int utilityIndex;
	char* utilityName;
	Utility* utility;

	// utility 1
	utilityIndex = 12;
	utilityName = "Electric Company";
	utility = Utility_new(utilityName);
	Field_delete(board->fields[utilityIndex]);
	board->fields[utilityIndex] = Field_new(FieldType_UTILITY, utilityName, utility, Effect_utility);
	board->utilities[0] = utility;

	// utility 2
	utilityIndex = 28;
	utilityName = "Water Works";
	utility = Utility_new(utilityName);
	Field_delete(board->fields[utilityIndex]);
	board->fields[utilityIndex] = Field_new(FieldType_UTILITY, utilityName, utility, Effect_utility);
	board->utilities[1] = utility;

	return board;
}

void Board_delete(Board* board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		Field_delete(board->fields[i]);
	}

	for (int i = 0; i < board->realties->size; ++i) {
		Realty* realty = *((Realty**)ArrayList_get(board->realties, i));
		Realty_delete(realty);
	}
	ArrayList_delete(board->realties);

	for (int i = 0; i < 4; ++i) {
		Rail_delete(board->railroads[i]);
	}

	for (int i = 0; i < 2; ++i) {
		Utility_delete(board->utilities[i]);
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

int Board_getJailIndex() {
	return jailIndex;
}

int Board_getColorCount(Color color) {
	assert(color >= 0 && color < ARRAY_LENGTH(colorCounts));

	return colorCounts[color];
}
