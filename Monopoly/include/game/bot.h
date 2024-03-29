#pragma once
#include <stdbool.h>

#include <core.h>

struct Bot {
	void* DELETEME;
};

Player* Bot_new(int id);

void Bot_delete(Player* bot);

int Bot_throwDice(bool* isDouble);

void Bot_onRealtyEvent(Player* bot, Game* game, Realty* realty);

void Bot_onRailroadEvent(Player* bot, Game* game, Rail* rail);

void Bot_onUtilityEvent(Player* bot, Game* game, Utility* utility);

JailEscapeOption Bot_onJailEvent(Player* player, Game* game);
