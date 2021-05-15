#include <stdlib.h>

#include <game/dice.h>

int Dice_throw() {
	return (rand() % 6) + 1;
}