#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <game/rail.h>
#include <config.h>

Rail* Rail_new(const char* name) {
	Rail* rail = malloc(sizeof(Rail));
	assert(rail);

	rail->name = strdup(name);
	rail->price = Constant_railCost;
	rail->rent[0] = Constant_railRent1;
	rail->rent[1] = Constant_railRent2;
	rail->rent[2] = Constant_railRent3;
	rail->rent[3] = Constant_railRent4;
	rail->owner = NULL;

	return rail;
}

void Rail_delete(Rail* rail) {
	if (rail->name) {
		free(rail->name);
	}
	free(rail);
}