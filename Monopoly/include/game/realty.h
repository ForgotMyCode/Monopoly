#pragma once

struct Player;

#include <game/player.h>

struct Realty {
	char* name;
	long price;
	long pricePerHouse;
	long rent[5];
	long rentHotel;
	long mortgage;
	struct Player* owner;
};

typedef struct Realty Realty;

Realty* Realty_new();

void Realty_delete(Realty* realty);
