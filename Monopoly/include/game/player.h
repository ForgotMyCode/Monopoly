#pragma once
#include <stdio.h>
#include <stdbool.h>

struct Game;
struct Realty;

#include <game/game.h>
#include <util/arraylist.h>
#include <game/bot.h>
#include <game/realty.h>

typedef unsigned char PlayerType;

union PlayerController {
	struct Bot* asBot;
};

typedef union PlayerController PlayerController;

struct Player {
	PlayerType playerType;
	union PlayerController playerController;
	struct ArrayList* ownedRealties;
	int position;
	long money;
	bool bankrupt;
};

typedef struct Player Player;

static const PlayerType PlayerType_BOT = 0;

void Player_super(Player* player);

void Player_delete(Player* player);

void Player_print(Player* player);

int Player_throwDice(Player* player);

void Player_onRealtyEvent(Player* player, struct Game* game, struct Realty* realty);


