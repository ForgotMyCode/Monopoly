#pragma once
#include <stdbool.h>

#include <core.h>
#include <game/player.h>
#include <game/board.h>
#include <game/realty.h>

struct Game {
	int playerCount;
	int activePlayers;
	Player** players;
	Board* board;
};

Game* Game_new(const int playerCount);

void Game_delete(Game* game);

void Game_setPlayer(Game* game, int playerIndex, Player* player);

void Game_deleteAllPlayers(Game* game);

void Game_addMoneyToPlayerByReference(Game* game, Player* player, long money);

void Game_addMoneyToPlayer(Game* game, int playerIndex, long money);

void Game_addMoneyToAllPlayers(Game* game, long money);

void Game_sendPlayerToJail(Game* game, Player* player);

void Game_start(Game* game);

void Game_movePlayerForward(Game* game, Player* player, int diceThrow);

bool Game_tryTransaction(Player* from,  Player* to, long amount);

void Game_playerReceiveRealty(Game* game, Player* player, Realty* realty);

void Game_purchaseRealty(Game* game, Player* player, Realty* realty);

void Game_onBankrupt(Game* game, Player* player, Player* creditor);

void Game_tryToGetOutOfJail(Game* game, Player* player, JailEscapeOption jailEscapeOption);

void Game_print(Game* game);
