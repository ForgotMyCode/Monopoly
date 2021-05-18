#pragma once

struct Player;
struct Game;
struct Realty;

#include <game/player.h>

struct Bot {
	void* DELETEME;
};

typedef struct Bot Bot;

struct Player* Bot_new(int id);

void Bot_delete(struct Player* bot);

int Bot_throwDice();

void Bot_onRealtyEvent(struct Player* bot, struct Game* game, struct Realty* realty);
