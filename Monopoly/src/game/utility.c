#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <game/utility.h>
#include <config.h>

Utility* Utility_new(const char* name) {
	Utility* utility = malloc(sizeof(Utility));
	assert(utility);

	utility->name = strdup(name);
	utility->price = Constant_utilityCost;
	utility->owner = NULL;

	return utility;
}

void Utility_delete(Utility* utility) {
	if (utility->name) {
		free(utility->name);
	}
	free(utility);
}