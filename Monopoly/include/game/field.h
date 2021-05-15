#pragma once
#include <stdio.h>

struct Field;
struct Game;
struct Player;

#include <game/game.h>
#include <game/player.h>
#include <game/realty.h>

struct Field {
	void (*apply)(struct Field* field, struct Game* game, struct Player* player);
	char* label;
	void* extra;
};

typedef struct Field Field;

struct Field* Field_new(char* label, void* extra, void (*apply)(Field* field, struct Game* game, struct Player* player));

void Field_delete(Field* field);

void Effect_notYetImplemented(Field* field, struct Game* game, struct Player* player);

void Effect_realty(Field* field, struct Game* game, struct Player* player);
