#pragma once
#include <stdio.h>
#include <stdbool.h>

#include <core.h>
#include <game/game.h>
#include <util/arraylist.h>
#include <game/bot.h>
#include <game/realty.h>

union PlayerController {
	void* asAnything;
	struct Bot* asBot;
};

struct Player {
	PlayerType playerType;
	union PlayerController playerController;
	struct ArrayList* ownedRealties;
	long money;
	long netWorth;
	int position;
	int id;
	int successiveDoubles;
	bool bankrupt;
	bool isInJail;
};

static const PlayerType PlayerType_UNKNOWN = 0;
static const PlayerType PlayerType_BOT = 1;

void Player_super(Player* player);

void Player_delete(Player* player);

void Player_print(Player* player);

void Player_printOnBoard(Player* player, int position);

int Player_throwDice(Player* player);

void Player_onRealtyEvent(Player* player, struct Game* game, struct Realty* realty);




