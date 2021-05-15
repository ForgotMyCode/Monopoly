#pragma once

#define ARRAYLIST_BUFFER_DEFAULTSIZE 8

typedef struct ArrayList ArrayList;

struct ArrayList {
	size_t size;
	size_t itemSize;
	size_t _buffer_size;
	void* buffer;
};

ArrayList* ArrayList_new(size_t itemSize);

void ArrayList_delete(ArrayList* list);

void ArrayList_add(ArrayList* list, void* item);

void* ArrayList_get(ArrayList* list, int index);
