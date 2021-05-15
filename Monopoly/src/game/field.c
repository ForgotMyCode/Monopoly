#include <stdio.h>
#include <assert.h>

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <game/field.h>
#include <util/arraylist.h>
#include <util/input.h>

Field* Field_new(char* label, void* extra, void (*apply)(Field* field, Game* game, Player* player)) {
	Field* field = malloc(sizeof(Field));
	assert(field);

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
