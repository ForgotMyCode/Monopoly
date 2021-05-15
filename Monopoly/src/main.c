#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <game/game.h>
#include <util/input.h>
#include <game/bot.h>
#include <util/arraylist.h>

int main(void) {
	srand(time(NULL));
	int playerCount = -1;

	readInt(&playerCount);
	assert(playerCount != -1);

	Game* monopolyGame = Game_new(playerCount);

	for (int i = 0; i < playerCount; ++i) {
		Game_setPlayer(monopolyGame, i, Bot_new());
	}

	Game_addMoneyToAllPlayers(monopolyGame, 1500L);

	Game_print(monopolyGame);

	Game_start(monopolyGame);

	Game_delete(monopolyGame);

	return 0;
}