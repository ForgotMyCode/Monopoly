#include <game/field.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <config.h>
#include <game/game.h>
#include <game/player.h>
#include <game/rail.h>
#include <game/realty.h>
#include <game/utility.h>
#include <util/arraylist.h>
#include <util/input.h>
#include <util/mathutils.h>

Field* Field_new(FieldType fieldType, char* label, void* extra, void (*apply)(Field* field, Game* game, Player* player)) {
	Field* field = malloc(sizeof(Field));
	assert(field);

	field->fieldType = fieldType;
	field->label = strdup(label);
	field->apply = apply;
	field->extra = extra;

	return field;
}

void Field_delete(Field* field) {
	if (field->label) {
		free(field->label);
	}
	free(field);
}

void Field_printOwnedStatus(Field* field) {
	if (field->fieldType == FieldType_REALTY) {
		Realty* const realty = (Realty*)field->extra;
		printf("%c", realty->owner == NULL ? 'U' : 'O');
	}
	else {
		printf(".");
	}
}

void Field_printOwner(Field* field) {
	if (field->fieldType == FieldType_REALTY) {
		Realty* const realty = (Realty*)field->extra;
		if (realty->owner == NULL) {
			printf(".");
		}
		else {
			printf("%d", realty->owner->id);
		}
	}
	else {
		printf(".");
	}
}

void Effect_notYetImplemented(Field* field, Game* game, Player* player) {
	printf("[ERROR] Not yet implemented!\n");
}

void Effect_realty(Field* field, Game* game, Player* player) {
	printf(">> Applying effect of realty...\n");
	Realty* realty = (Realty*)field->extra;
	if (realty->owner != NULL && player != realty->owner) {
		long rent = 0;
		const int ownedRealtiesOfThisColor = realty->owner->ownedRealtiesColorCounts[realty->color];
		const int totalRealtiesOfThisColor = Board_getColorCount(realty->color);
		printf("[DBG] %d / %d\n", ownedRealtiesOfThisColor, totalRealtiesOfThisColor);

		if (ownedRealtiesOfThisColor < totalRealtiesOfThisColor) {
			rent = realty->rent[0];
		}
		else {
			printf(">> Double rent!\n");
			assert(ownedRealtiesOfThisColor == totalRealtiesOfThisColor);
			rent = 2L * realty->rent[0];
		}

		if (!Game_tryTransaction(player, realty->owner, rent)) {
			Game_onBankrupt(game, player, realty->owner);
		}
	}
	Player_onRealtyEvent(player, game, realty);
}

void Effect_Tax(Field* field, Game* game, Player* player) {
	long tax = 0;

	if (field->fieldType == FieldType_TAX_INCOME) {
		tax = min(player->netWorth / 10L, Constant_incomeSolidTax);
	}
	else if (field->fieldType == FieldType_TAX_LUXURY) {
		tax = Constant_luxuryTax;
	}
	else {
		assert(false);
	}

	if (!Game_tryTransaction(player, NULL, tax)) {
		Game_onBankrupt(game, player, NULL);
	}
}

void Effect_goToJail(Field* field, Game* game, Player* player) {
	Game_sendPlayerToJail(game, player);
}

void Effect_visitJail(Field* field, Game* game, Player* player) {
	
}

void Effect_railroad(Field* field, Game* game, Player* player) {
	printf(">> Applying effect of railroad...\n");
	Rail* rail = (Rail*)field->extra;
	assert(rail);

	if (rail->owner != NULL && player != rail->owner) {
		assert(rail->owner->ownedRails->size - 1 >= 0);
		if (!Game_tryTransaction(player, rail->owner, rail->rent[rail->owner->ownedRails->size - 1])) {
			Game_onBankrupt(game, player, rail->owner);
		}
	}
	Player_onRailroadEvent(player, game, rail);
}

void Effect_utility(Field* field, Game* game, Player* player) {
	printf(">> Applying effect of utility...\n");
	Utility* utility = (Utility*)field->extra;
	assert(utility);

	if (utility->owner != NULL && player != utility->owner) {
		assert(utility->owner->ownedRails->size - 1 >= 0);

		long multiplier = 0L;
		if (utility->owner->ownedUtilities->size == 1) {
			multiplier = Constant_utilityMultiplier1;
		}
		else if (utility->owner->ownedUtilities->size == 2) {
			multiplier = Constant_utilityMultiplier2;
		}
		else {
			printf("[ERROR] Invalid amount of owned utilities: %lu\n", (unsigned long) utility->owner->ownedUtilities->size);
			assert(false);
		}

		long lastRoll = (long) game->diceRoll;

		if (!Game_tryTransaction(player, utility->owner, lastRoll * multiplier)) {
			Game_onBankrupt(game, player, utility->owner);
		}
	}
	Player_onUtilityEvent(player, game, utility);
}
