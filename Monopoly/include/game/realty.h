#pragma once

#include <game/player.h>

typedef struct Realty Realty; 

struct Realty {
	char* name;
	long price;
	long pricePerHouse;
	long rent[5];
	long rentHotel;
	long mortgage;
	struct Player* owner;
};

Realty* Realty_new();

void Realty_delete(Realty* realty);
