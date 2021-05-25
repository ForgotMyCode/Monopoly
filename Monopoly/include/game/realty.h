#pragma once
#include <core.h>
#include <game/player.h>

struct Realty {
	char* name;
	long price;
	long pricePerHouse;
	long rent[5];
	long rentHotel;
	long mortgage;
	Player* owner;
};

Realty* Realty_new();

void Realty_delete(Realty* realty);
