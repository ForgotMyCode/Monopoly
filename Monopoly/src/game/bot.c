#include <game/bot.h>

#include <assert.h>
#include <stdlib.h>

#include <config.h>
#include <game/dice.h>
#include <game/jail.h>
#include <game/player.h>
#include <game/rail.h>
#include <game/realty.h>
#include <game/utility.h>

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

int Bot_throwDice(bool* isDouble) {
	const int dieResult1 = Dice_throw();
	const int dieResult2 = Dice_throw();
	
	*isDouble = dieResult1 == dieResult2;

	return dieResult1 + dieResult2;
}

void Bot_onRealtyEvent(Player* bot, Game* game, Realty* realty) {
	if (realty->owner == NULL && bot->money >= realty->price + 50) {
		printf(">> Purchasing the realty %s...\n", realty->name);
		Game_purchaseRealty(game, bot, realty);
	}
}

void Bot_onRailroadEvent(Player* bot, Game* game, Rail* rail) {
	if (rail->owner == NULL && bot->money >= rail->price + 50) {
		printf(">> Purchasing the railroad %s...\n", rail->name);
		Game_purchaseRailroad(game, bot, rail);
	}
}

void Bot_onUtilityEvent(Player* bot, Game* game, Utility* utility) {
	if (utility->owner == NULL && bot->money >= utility->price + 50) {
		printf(">> Purchasing the utility %s...\n", utility->name);
		Game_purchaseUtility(game, bot, utility);
	}
}

JailEscapeOption Bot_onJailEvent(Player* player, Game* game) {
	if (player->failedJailEscapes < Constant_maxFailedJailEscapes) {
		return JAIL_ESCAPE_OPTION_ROLL;
	}
	if (player->money >= Constant_getOutOfJailFee) {
		return JAIL_ESCAPE_OPTION_PAY;
	}
	return JAIL_ESCAPE_OPTION_SKIP;
}
