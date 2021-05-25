#pragma once
#include <core.h>
#include <game/player.h>

struct Bot {
	void* DELETEME;
};

Player* Bot_new(int id);

void Bot_delete(Player* bot);

int Bot_throwDice();

void Bot_onRealtyEvent(Player* bot, Game* game, Realty* realty);
