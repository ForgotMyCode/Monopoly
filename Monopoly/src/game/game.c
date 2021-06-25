#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <game/game.h>
#include <config.h>
#include <game/board.h>
#include <game/field.h>
#include <game/jail.h>
#include <game/player.h>
#include <game/rail.h>
#include <game/realty.h>
#include <game/utility.h>
#include <util/arraylist.h>

Game* Game_new(const int playerCount) {
	Game* game = malloc(sizeof(Game));
	assert(game);

	game->playerCount = playerCount;
	game->activePlayers = 0;
	game->diceRoll = 0;
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

void Game_sendPlayerToJail(Game* game, Player* player) {
	printf(">> Player sent to jail!\n");
	player->isInJail = true;
	player->position = Board_getJailIndex();
	player->failedJailEscapes = 0;
}

void Game_checkForGo(Player* currentPlayer) {
	while (currentPlayer->position >= BOARD_SIZE) {
		printf(">> Round finished!\n");
		// round finished
		currentPlayer->position -= BOARD_SIZE;
		Game_tryTransaction(NULL, currentPlayer, Constant_moneyPerRound);
	}
}

void Game_finishMove(Game* game, Player* player) {
	if (!player->bankrupt) {
		++game->activePlayers;
	}
}

void Game_movePlayerForward(Game* game, Player* player, int diceThrow) {
	printf(">> Moving player by %d.\n", diceThrow);

	player->position += diceThrow;

	Game_checkForGo(player);

	printf(">> Steps on field %d...\n", player->position);

	Field* const currentField = game->board->fields[player->position];
	currentField->apply(currentField, game, player);
}

void Game_checkPlayerInJail(Game* game, Player* player) {
	if (player->isInJail) {
		JailEscapeOption jailEscapeOption = Player_onJailEvent(player, game);
		Game_tryToGetOutOfJail(game, player, jailEscapeOption);
	}
}

void Game_start(Game* game) {
	game->activePlayers = game->playerCount;

	while (game->activePlayers > 1u) {
		game->activePlayers = 0u;
		Game_print(game);
		for (int player = 0; player < game->playerCount; ++player) {
			printf("It's Player's %d turn...\n", player);

			Player* const currentPlayer = game->players[player];

			if (currentPlayer->bankrupt) {
				printf(">> Bankrupt, skipping...\n");
				continue;
			}

			Player_newRound(currentPlayer);

			Game_checkPlayerInJail(game, currentPlayer);

			if (currentPlayer->isInJail) {
				Game_finishMove(game, currentPlayer);
				continue;
			}

			if (currentPlayer->skipTurn) {
				currentPlayer->skipTurn = false;
				Game_finishMove(game, currentPlayer);
				continue;
			}

			bool threwDouble = false;
			do {
				threwDouble = false;

				game->diceRoll = Player_throwDice(currentPlayer, &threwDouble);
				assert(game->diceRoll >= 2 && game->diceRoll <= 12);

				printf(">> Threw %d total! It was %sa double!\n", game->diceRoll, threwDouble ? "" : "not ");

				++currentPlayer->successiveDoubles;
				if (currentPlayer->successiveDoubles >= Constant_doublesBeforeJail) {
					Game_sendPlayerToJail(game, currentPlayer);
					Game_finishMove(game, currentPlayer);
					break;
				}

				Game_movePlayerForward(game, currentPlayer, game->diceRoll);
				Game_finishMove(game, currentPlayer);
			} while (threwDouble && !currentPlayer->isInJail);
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

	if (player != NULL) {
		ArrayList_add(player->ownedRealties, &realty);
		player->netWorth += realty->price;
		++(player->ownedRealtiesColorCounts[realty->color]);
	}
}

void Game_playerReceiveRailroad(Game* game, Player* player, Rail* rail) {
	printf(">> Railroad received: %s\n", rail->name);
	rail->owner = player;

	if (player != NULL) {
		ArrayList_add(player->ownedRails, &rail);
		player->netWorth += rail->price;
	}
}

void Game_playerReceiveUtility(Game* game, Player* player, Utility* utility) {
	printf(">> Utility received: %s\n", utility->name);
	utility->owner = player;

	if (player != NULL) {
		ArrayList_add(player->ownedUtilities, &utility);
		player->netWorth += utility->price;
	}
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

void Game_purchaseRailroad(Game* game, Player* player, Rail* rail) {
	if (rail->owner != NULL) {
		printf("[WARN] Player did an invalid move! Cannot buy owned property!\n");
		return;
	}

	if (!Game_tryTransaction(player, NULL, rail->price)) {
		printf("[WARN] Player did an invalid move! Not enough money!");
		return;
	}

	Game_playerReceiveRailroad(game, player, rail);
}

void Game_purchaseUtility(Game* game, Player* player, Utility* utility) {
	if (utility->owner != NULL) {
		printf("[WARN] Player did an invalid move! Cannot buy owned property!\n");
		return;
	}

	if (!Game_tryTransaction(player, NULL, utility->price)) {
		printf("[WARN] Player did an invalid move! Not enough money!");
		return;
	}

	Game_playerReceiveUtility(game, player, utility);
}

void Game_onBankrupt(Game* game, Player* player, Player* creditor) {
	player->bankrupt = true;

	for (int i = 0; i < player->ownedRealties->size; ++i) {
		Realty* const realty = *((Realty**)ArrayList_get(player->ownedRealties, i));
		Game_playerReceiveRealty(game, creditor, realty);
	}

	for (int i = 0; i < player->ownedRails->size; ++i) {
		Rail* const rail = *((Rail**)ArrayList_get(player->ownedRails, i));
		Game_playerReceiveRailroad(game, creditor, rail);
	}

	if (player->money > 0L) {
		Game_tryTransaction(player, creditor, player->money);
	}
}

void Game_tryToGetOutOfJail(Game* game, Player* player, JailEscapeOption jailEscapeOption) {
	printf(">> Player is trying to get out of jail...\n");
	if (jailEscapeOption == JAIL_ESCAPE_OPTION_PAY) {
		if (Game_tryTransaction(player, NULL, Constant_getOutOfJailFee)) {
			printf(">> Paid fee...\n");
			player->isInJail = false;
			return;
		}

		printf("[WARN] Invalid move! Player don't have enough money to pay the jail escape fee!\n");
		printf(">> Fix: Skipping turn instead...\n");

		Game_tryToGetOutOfJail(game, player, JAIL_ESCAPE_OPTION_SKIP);

		return;
	}
	if (jailEscapeOption == JAIL_ESCAPE_OPTION_ROLL) {
		if (player->failedJailEscapes < Constant_maxFailedJailEscapes) {
			printf(">> Rolls..\n");
			++player->failedJailEscapes;

			bool threwDouble = false;

			game->diceRoll = Player_throwDice(player, &threwDouble);

			if (threwDouble) {
				printf(">> Success!\n");
				player->isInJail = false;
				player->skipTurn = true;
				Game_movePlayerForward(game, player, game->diceRoll);
			}
			printf(">> Failed...\n");
			return;
		}

		printf("[WARN] Invalid move! Player already tried to escape too many times!\n");
		printf(">> Fix: Skipping turn instead...\n");

		Game_tryToGetOutOfJail(game, player, JAIL_ESCAPE_OPTION_SKIP);

		return;
	}
	if (jailEscapeOption == JAIL_ESCAPE_OPTION_SKIP) {
		printf(">> Skips...\n");
		player->isInJail = false;
		player->skipTurn = true;
		return;
	}

	printf("[ERROR] Invalid jail escape option!\n");
	assert(false);
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
