#include <game/dice.h>

#include <stdlib.h>

int Dice_throw() {
	return (rand() % 6) + 1;
}