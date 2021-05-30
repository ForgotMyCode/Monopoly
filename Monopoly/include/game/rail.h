#pragma once

#include <core.h>
#include <game/player.h>

struct Rail {
	char* name;
	long price;
	long rent[4];
	Player* owner;
};

Rail* Rail_new(const char* name);

void Rail_delete(Rail* rail);
