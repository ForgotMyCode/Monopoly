#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <game/game.h>
#include <util/input.h>
#include <game/bot.h>
#include <util/arraylist.h>
#include <util/random.h>

int main(void) {
	srand(time(NULL));
	seed_prng_state(PRNG_DICE, 1);
	int playerCount = -1;

	readInt(&playerCount);
	assert(playerCount != -1);

	initializePrng();

	Game* monopolyGame = Game_new(playerCount);

	for (int i = 0; i < playerCount; ++i) {
		Game_setPlayer(monopolyGame, i, Bot_new(i));
	}

	Game_addMoneyToAllPlayers(monopolyGame, 1500L);

	Game_start(monopolyGame);

	Game_delete(monopolyGame);

	return 0;
}