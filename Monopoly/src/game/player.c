#include <stdio.h>

#include <game/player.h>
#include <game/bot.h>
#include <game/game.h>
#include <game/realty.h>

void Player_super(Player* player) {
	player->playerType = PlayerType_UNKNOWN;
	player->playerController.asAnything = NULL;
	player->ownedRealties = ArrayList_new(sizeof(Realty*));
	player->money = 0;
	player->id = -1;
	player->bankrupt = false;
	player->position = 0;
}

void Player_delete(Player* player) {
	if (!player->bankrupt) {
		for (int i = 0; i < player->ownedRealties->size; ++i) {
			Realty* const realty = *((Realty**)ArrayList_get(player->ownedRealties, i));
			Realty_delete(realty);
		}
	}

	ArrayList_delete(player->ownedRealties);

	if (player->playerType == PlayerType_BOT) {
		Bot_delete(player);
	}
}

void Player_print(Player* player) {
	printf("Player ID: %d\n", player->id);
	printf("Balance: %ld\n", player->money);
}

void Player_printOnBoard(Player* player, int position) {
	printf("%c", player->position == position ? '#' : '.');
}

int Player_throwDice(Player* player) {
	if (player->playerType == PlayerType_BOT) {
		return Bot_throwDice();
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
}
