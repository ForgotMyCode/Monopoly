#pragma once
#include <stdbool.h>

struct Player;
struct Board;
struct Realty;

#include <game/player.h>
#include <game/board.h>
#include <game/realty.h>

struct Game {
	int playerCount;
	struct Player** players;
	struct Board* board;
};

typedef struct Game Game;

struct Game* Game_new(const int playerCount);

void Game_delete(Game* game);

void Game_setPlayer(Game* game, int playerIndex, struct Player* player);

void Game_deleteAllPlayers(Game* game);

void Game_addMoneyToPlayerByReference(Game* game, struct Player* player, long money);

void Game_addMoneyToPlayer(Game* game, int playerIndex, long money);

void Game_addMoneyToAllPlayers(Game* game, long money);

void Game_start(Game* game);

bool Game_tryTransaction(struct Player* from, struct  Player* to, long amount);

void Game_playerReceiveRealty(Game* game, struct Player* player, struct Realty* realty);

void Game_purchaseRealty(Game* game, struct Player* player, struct Realty* realty);

void Game_onBankrupt(Game* game, struct Player* player, struct Player* creditor);

void Game_print(Game* game);
