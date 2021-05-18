#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include <util/arraylist.h>
#include <util/input.h>
#include <game/realty.h>
#include <config.h>
#include <util/random.h>

void readInt(int* n) {
	register int c;
	int x = 0;
	do {
#ifdef UNIX
		c = getchar_unlocked();
#else
		c = getchar();
#endif
	} while (c < '0' || c > '9');
	do {
		x = 10 * x + c - '0';
#ifdef UNIX
		c = getchar_unlocked();
#else
		c = getchar();
#endif
	} while (!(c < '0' || c > '9'));
	*n = x;
}

void freadLong(long* n, FILE* f) {
	register int c;
	long x = 0L;
	do {
		c = getc(f);
	} while (c < '0' || c > '9');
	do {
		x = 10 * x + c - '0';
		c = getc(f);
	} while (!(c < '0' || c > '9'));
	*n = x;
}

bool isStdChar(char c) {
	return c >= ' ';
}

ArrayList* readCSVLine(FILE* file) {
	ArrayList* list = ArrayList_new(sizeof(char));

	int read;
	char c;

	do {
		read = getc(file);
		c = (char)read;
		ArrayList_add(list, &c);
	} while (read != EOF && c != '\n');

	((char*) list->buffer)[list->size - 1] = '\0';

	return list;
}

ArrayList* parseCSV(char* filename) {
	FILE* f = fopen(filename, "r");
	assert(f);

	ArrayList* firstLine = readCSVLine(f);
	ArrayList_delete(firstLine);

	ArrayList* realties = ArrayList_new(sizeof(Realty*));

	while (true) {
		ArrayList* line = readCSVLine(f);

		if (line->size <= 1) {
			ArrayList_delete(line);
			break;
		}

		char* str = strdup((char*) line->buffer);
		char* split;
		char* strBuffer = str;

		ArrayList_delete(line);

		Realty* realty = Realty_new();

		// name
		split = strtok(str, ",");
		assert(split);

		realty->name = strdup(split);

		// price
		split = strtok(NULL, ",");
		assert(split);

		realty->price = atol(split);

		// price per house
		split = strtok(NULL, ",");
		assert(split);

		realty->pricePerHouse = atol(split);

		// rent
		split = strtok(NULL, ",");
		assert(split);

		realty->rent[0] = atol(split);
		
		// rent 1
		split = strtok(NULL, ",");
		assert(split);

		realty->rent[1] = atol(split);

		// rent 2
		split = strtok(NULL, ",");
		assert(split);

		realty->rent[2] = atol(split);

		// rent 3
		split = strtok(NULL, ",");
		assert(split);

		realty->rent[3] = atol(split);

		// rent 4
		split = strtok(NULL, ",");
		assert(split);

		realty->rent[4] = atol(split);

		// rent hotel
		split = strtok(NULL, ",");
		assert(split);

		realty->rentHotel = atol(split);

		// mortgage
		split = strtok(NULL, ",");
		assert(split);

		realty->mortgage = atol(split);

		free(strBuffer);

		ArrayList_add(realties, &realty);
	}

	fclose(f);

	return realties;
}

void initializePrng() {
	int value = -1;
	for (int i = 0; i < PRNG_STATES_COUNT; ++i) {
		readInt(&value);
		seed_prng_state(i, value);
	}
}
