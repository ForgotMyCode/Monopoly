#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <game/game.h>
#include <config.h>

Game* Game_new(const int playerCount) {
	Game* game = malloc(sizeof(Game));
	assert(game);

	game->playerCount = playerCount;
	game->players = malloc(sizeof(Player*) * playerCount);
	game->board = Board_new("properties.csv");

	return game;
}

void Game_delete(Game* game) {
	for (int i = 0; i < game->playerCount; ++i) {
		Player_delete(game->players[i]);
	}
	Board_delete(game->board);
	free(game->players);
	free(game);
}

void Game_setPlayer(Game* game, int playerIndex, Player* player) {
	game->players[playerIndex] = player;
}

void Game_deleteAllPlayers(Game* game) {
	for (int i = 0; i < game->playerCount; ++i) {
		Player_delete(game->players[i]);
	}
}

void Game_addMoneyToPlayerByReference(Game* game, Player* player, long money) {
	player->money += money;
}

void Game_addMoneyToPlayer(Game* game, int playerIndex, long money) {
	Game_addMoneyToPlayerByReference(game, game->players[playerIndex], money);
}

void Game_addMoneyToAllPlayers(Game* game, long money) {
	for (int i = 0; i < game->playerCount; ++i) {
		Game_addMoneyToPlayer(game, i, money);
	}
}

void Game_start(Game* game) {
	int activePlayers = game->playerCount;

	while (activePlayers > 1u) {
		activePlayers = 0u;
		Game_print(game);
		for (int player = 0; player < game->playerCount; ++player) {
			printf("It's Player's %d turn...\n", player);

			Player* const currentPlayer = game->players[player];

			if (currentPlayer->bankrupt) {
				printf(">> Bankrupt, skipping...\n");
				continue;
			}

			int diceThrow = Player_throwDice(currentPlayer);
			assert(diceThrow >= 2 && diceThrow <= 12);

			printf(">> Threw %d total!\n", diceThrow);

			currentPlayer->position += diceThrow;


			while (currentPlayer->position >= BOARD_SIZE) {
				printf(">> Round finished!\n");
				// round finished
				currentPlayer->position -= BOARD_SIZE;
				Game_tryTransaction(NULL, currentPlayer, Constant_moneyPerRound);
			}

			printf(">> Steps on field %d...\n", currentPlayer->position);

			Field* const currentField = game->board->fields[currentPlayer->position];
			currentField->apply(currentField, game, currentPlayer);

			if (!currentPlayer->bankrupt) {
				++activePlayers;
			}
		}
	}
	printf("\n --- GAME OVER --- \n");
}

bool Game_tryTransaction(Player* from, Player* to, long amount) {
	printf(">> Transaction of $%ld...\n", amount);

	if (from == NULL) {
		assert(to);

		to->money += amount;
		return true;
	}

	if (from->money < amount) {
		printf(">> FAILED\n");
		return false;
	}

	if (to != NULL) {
		to->money += amount;
	}
	from->money -= amount;

	return true;
}

void Game_playerReceiveRealty(Game* game, Player* player, Realty* realty) {
	printf(">> Realty received: %s\n", realty->name);
	realty->owner = player;
	ArrayList_add(player->ownedRealties, &realty);
	player->netWorth += realty->price;
}

void Game_purchaseRealty(Game* game, Player* player, Realty* realty) {
	if (realty->owner != NULL) {
		printf("[WARN] Player did an invalid move! Cannot buy owned property!\n");
		return;
	}

	if (!Game_tryTransaction(player, NULL, realty->price)) {
		printf("[WARN] Player did an invalid move! Not enough money!");
		return;
	}

	Game_playerReceiveRealty(game, player, realty);
}

void Game_onBankrupt(Game* game, Player* player, Player* creditor) {
	player->bankrupt = true;

	for (int i = 0; i < player->ownedRealties->size; ++i) {
		Realty* const realty = *((Realty**)ArrayList_get(player->ownedRealties, i));
		Game_playerReceiveRealty(game, creditor, realty);
	}

	if (player->money > 0L) {
		Game_tryTransaction(player, creditor, player->money);
	}
}

void Game_print(Game* game) {
	printf("---BOARD: Owned status: ---\n");
	Board_print(game->board, BoardPrintMode_OWNEDSTATUS);
	printf("---BOARD: Owners: ---\n");
	Board_print(game->board, BoardPrintMode_OWNERS);

	for (int i = 0; i < game->playerCount; ++i) {
		printf("PLAYER n.%d:\n", i);
		Board_printForPlayer(game->board, game->players[i]);
		Player_print(game->players[i]);
	}
}
