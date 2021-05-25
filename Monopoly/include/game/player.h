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
	Bot* asBot;
};

struct Player {
	PlayerType playerType;
	PlayerController playerController;
	ArrayList* ownedRealties;
	long money;
	long netWorth;
	int position;
	int id;
	int successiveDoubles;
	int failedJailEscapes;
	bool bankrupt;
	bool isInJail;
	bool skipTurn;
};

static const PlayerType PlayerType_UNKNOWN = 0;
static const PlayerType PlayerType_BOT = 1;

void Player_super(Player* player);

void Player_delete(Player* player);

void Player_print(Player* player);

void Player_newRound(Player* player);

void Player_printOnBoard(Player* player, int position);

int Player_throwDice(Player* player, bool* isDouble);

void Player_onRealtyEvent(Player* player, Game* game, Realty* realty);

JailEscapeOption Player_onJailEvent(Player* player, Game* game);
