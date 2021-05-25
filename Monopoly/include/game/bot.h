#pragma once
#include <stdbool.h>

#include <core.h>
#include <game/player.h>

struct Bot {
	void* DELETEME;
};

Player* Bot_new(int id);

void Bot_delete(Player* bot);

int Bot_throwDice(bool* isDouble);

void Bot_onRealtyEvent(Player* bot, Game* game, Realty* realty);
