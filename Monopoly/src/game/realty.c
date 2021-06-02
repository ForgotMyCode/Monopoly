#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <game/realty.h>

Realty* Realty_new() {
	Realty* realty = malloc(sizeof(Realty));
	assert(realty);

	realty->name = NULL;
	realty->color = -1;
	realty->price = -1;
	realty->pricePerHouse = -1;
	realty->rent[0] = -1;
	realty->rent[1] = -1;
	realty->rent[2] = -1;
	realty->rent[3] = -1;
	realty->rent[4] = -1;
	realty->rentHotel = -1;
	realty->mortgage = -1;
	realty->owner = NULL;

	return realty;
}

void Realty_delete(Realty* realty) {
	if (realty->name) {
		free(realty->name);
	}
	free(realty);
}