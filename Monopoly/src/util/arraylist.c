#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <util/arraylist.h>

typedef unsigned char byte;

ArrayList* ArrayList_new(size_t itemSize) {
	ArrayList* list = malloc(sizeof(ArrayList));
	assert(list);

	list->size = 0;
	list->itemSize = itemSize;
	list->_buffer_size = ARRAYLIST_BUFFER_DEFAULTSIZE;
	list->buffer = malloc(itemSize * ARRAYLIST_BUFFER_DEFAULTSIZE);

	return list;
}

void ArrayList_delete(ArrayList* list) {
	free(list->buffer);
	free(list);
}

void _ArrayList_check_realloc(ArrayList* list) {
	if (list->size >= list->_buffer_size) {
		list->_buffer_size *= 2;

		void* tmpBuffer = realloc(list->buffer, list->itemSize * list->_buffer_size);
		assert(tmpBuffer);

		list->buffer = tmpBuffer;
	}
}

void ArrayList_add(ArrayList* list, void* itemPtr) {
	_ArrayList_check_realloc(list);
	memcpy((byte*)list->buffer + list->itemSize * list->size, itemPtr, list->itemSize);
	++list->size;
}

void* ArrayList_get(ArrayList* list, int index) {
	assert(index < list->size);
	return (byte*) list->buffer + list->itemSize * index;
}