#include <assert.h>
#include <stdlib.h>

#include <game/bot.h>
#include <game/player.h>
#include <game/dice.h>

Player* Bot_new(int id) {
	Player* player = malloc(sizeof(Player));
	assert(player);

	Player_super(player);
	player->id = id;

	player->playerType = PlayerType_BOT;
	player->playerController.asBot = malloc(sizeof(Bot));
	assert(player->playerController.asBot);

	return player;
}

void Bot_delete(Player* bot) {
	free(bot->playerController.asBot);
	free(bot);
}

int Bot_throwDice() {
	const int dieResult1 = Dice_throw();
	const int dieResult2 = Dice_throw();
	return dieResult1 + dieResult2;
}

void Bot_onRealtyEvent(Player* bot, Game* game, Realty* realty) {
	if (realty->owner == NULL && bot->money >= realty->price + 50) {
		printf(">> Purchasing the realty %s...\n", realty->name);
		Game_purchaseRealty(game, bot, realty);
	}
}
