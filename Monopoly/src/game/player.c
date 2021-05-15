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
	if (player->playerType == PlayerType_BOT) {
		Bot_delete(player);
	}
}

void Player_print(Player* player) {
	printf("-----\n");

	printf("Money: %d\n", player->money);
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
