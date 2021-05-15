#pragma once

#include <game/player.h>

typedef struct Bot Bot; 

struct Bot {
	void* DELETEME;
};

struct Player* Bot_new();

void Bot_delete(struct Player* bot);

int Bot_throwDice();

void Bot_onRealtyEvent(struct Player* bot, struct Game* game, struct Realty* realty);
