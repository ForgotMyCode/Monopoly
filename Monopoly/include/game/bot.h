#pragma once
#include <core.h>
#include <game/player.h>

struct Bot {
	void* DELETEME;
};

struct Player* Bot_new(int id);

void Bot_delete(struct Player* bot);

int Bot_throwDice();

void Bot_onRealtyEvent(struct Player* bot, struct Game* game, struct Realty* realty);
