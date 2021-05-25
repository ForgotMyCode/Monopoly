#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <game/field.h>
#include <util/arraylist.h>
#include <util/input.h>
#include <config.h>
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
		if (!Game_tryTransaction(player, realty->owner, realty->rent[0])) {
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
