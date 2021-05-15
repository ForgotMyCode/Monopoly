#pragma once
#include <stdio.h>
#include <stdbool.h>

#include <game/game.h>
#include <util/arraylist.h>
#include <game/bot.h>
#include <game/realty.h>

typedef struct Player Player;

typedef union PlayerController PlayerController;

typedef unsigned char PlayerType;

union PlayerController {
	struct Bot* asBot;
};

struct Player {
	PlayerType playerType;
	union PlayerController playerController;
	struct ArrayList* ownedRealties;
	int position;
	long money;
	bool bankrupt;
};

static const PlayerType PlayerType_BOT = 0;

void Player_super(Player* player);

void Player_delete(Player* player);

void Player_print(Player* player);

int Player_throwDice(Player* player);

void Player_onRealtyEvent(Player* player, struct Game* game, struct Realty* realty);


