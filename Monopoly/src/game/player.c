#include <stdio.h>

#include <game/player.h>
#include <game/bot.h>
#include <game/game.h>
#include <game/realty.h>

void Player_super(Player* player) {
	player->ownedRealties = ArrayList_new(sizeof(Realty*));
	player->money = 0;
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
	printf("-----\n");

	printf("Money: %ld\n", player->money);
	printf("Position: %d\n", player->position);
	printf("Bankrupt: %d\n", player->bankrupt);

	printf("-----\n");
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
