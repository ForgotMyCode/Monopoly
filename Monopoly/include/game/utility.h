#pragma once

#include <core.h>

struct Utility {
	char* name;
	long price;
	Player* owner;
};

Utility* Utility_new(const char* name);

void Utility_delete(Utility* rail);
