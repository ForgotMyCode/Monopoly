#pragma once
#include <core.h>

struct Realty {
	char* name;
	Color color;
	long price;
	long pricePerHouse;
	long rent[5];
	long rentHotel;
	long mortgage;
	Player* owner;
};

Realty* Realty_new();

void Realty_delete(Realty* realty);
