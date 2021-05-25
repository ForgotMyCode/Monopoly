#pragma once
#include <stdio.h>

#include <core.h>
#include <game/game.h>
#include <game/player.h>
#include <game/realty.h>


static const FieldType FieldType_UNDEFINED = 0;
static const FieldType FieldType_REALTY = 1;

struct Field {
	void (*apply)(Field* field, Game* game, Player* player);
	char* label;
	void* extra;
	FieldType fieldType;
};

Field* Field_new(FieldType fieldType, char* label, void* extra, void (*apply)(Field* field, Game* game, Player* player));

void Field_delete(Field* field);

void Field_printOwnedStatus(Field* field);

void Field_printOwner(Field* field);

void Effect_notYetImplemented(Field* field, Game* game, Player* player);

void Effect_realty(Field* field, Game* game, Player* player);
