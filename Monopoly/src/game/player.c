#include <stdio.h>
#include <assert.h>

#include <game/player.h>
#include <game/bot.h>
#include <game/game.h>
#include <game/realty.h>
#include <config.h>
#include <game/jail.h>

void Player_super(Player* player) {
	player->playerType = PlayerType_UNKNOWN;
	player->playerController.asAnything = NULL;
	player->ownedRealties = ArrayList_new(sizeof(Realty*));
	player->ownedRails = ArrayList_new(sizeof(Rail*));
	player->netWorth = 0;
	player->money = 0;
	player->id = -1;
	player->bankrupt = false;
	player->position = 0;
	player->successiveDoubles = 0;
	player->failedJailEscapes = 0;
	player->isInJail = false;
	player->skipTurn = false;
}

void Player_delete(Player* player) {
	if (!player->bankrupt) {
		for (int i = 0; i < player->ownedRealties->size; ++i) {
			Realty* const realty = *((Realty**)ArrayList_get(player->ownedRealties, i));
			Realty_delete(realty);
		}

		for (int i = 0; i < player->ownedRails->size; ++i) {
			Rail* const rail = *((Rail**)ArrayList_get(player->ownedRails, i));
			Rail_delete(rail);
		}
	}

	ArrayList_delete(player->ownedRealties);
	ArrayList_delete(player->ownedRails);

	if (player->playerType == PlayerType_BOT) {
		Bot_delete(player);
	}
}

void Player_print(Player* player) {
	printf("Player ID: %d\n", player->id);
	printf("Balance: %ld\n", player->money);
	printf("Successive doubles: %d\n", player->successiveDoubles);
	printf("Net Worth: %ld\n", player->netWorth);
	printf("\n");
	printf("In jail: %s\n", player->isInJail ? "true" : "false");
	printf("Jail Rolls Remaining: %d\n", Constant_maxFailedJailEscapes - player->failedJailEscapes);
}

void Player_printOnBoard(Player* player, int position) {
	printf("%c", player->position == position ? '#' : '.');
}

void Player_newRound(Player* player) {
	player->successiveDoubles = 0;
}

int Player_throwDice(Player* player, bool* isDouble) {
	if (player->playerType == PlayerType_BOT) {
		return Bot_throwDice(isDouble);
	}
	
	printf("[ERROR] Invalid player type!\n");
	return -1;
}

void Player_onRealtyEvent(Player* player, Game* game, Realty* realty) {
	if (player->playerType == PlayerType_BOT) {
		Bot_onRealtyEvent(player, game, realty);
		return;
	}

	printf("[ERROR] Invalid player type!\n");
	assert(false);
}

void Player_onRailroadEvent(Player* player, Game* game, Rail* rail) {
	if (player->playerType == PlayerType_BOT) {
		Bot_onRailroadEvent(player, game, rail);
		return;
	}

	printf("[ERROR] Invalid player type!\n");
	assert(false);
}

JailEscapeOption Player_onJailEvent(Player* player, Game* game) {
	if (player->playerType == PlayerType_BOT) {
		return Bot_onJailEvent(player, game);
	}

	printf("[ERROR] Invalid player type!\n");
	assert(false);

	return JAIL_ESCAPE_OPTION_UNDEFINED;
}
