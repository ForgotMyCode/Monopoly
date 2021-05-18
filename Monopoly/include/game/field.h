#pragma once
#include <stdio.h>

struct Field;
struct Game;
struct Player;

#include <game/game.h>
#include <game/player.h>
#include <game/realty.h>

typedef unsigned char FieldType;

static const FieldType FieldType_UNDEFINED = 0;
static const FieldType FieldType_REALTY = 1;

struct Field {
	void (*apply)(struct Field* field, struct Game* game, struct Player* player);
	char* label;
	void* extra;
	FieldType fieldType;
};

typedef struct Field Field;

struct Field* Field_new(FieldType fieldType, char* label, void* extra, void (*apply)(Field* field, struct Game* game, struct Player* player));

void Field_delete(Field* field);

void Field_printOwnedStatus(Field* field);

void Field_printOwner(Field* field);

void Effect_notYetImplemented(Field* field, struct Game* game, struct Player* player);

void Effect_realty(Field* field, struct Game* game, struct Player* player);
