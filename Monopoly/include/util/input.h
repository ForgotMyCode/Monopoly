#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <util/arraylist.h>

void readInt(int* n);

void freadLong(long* n, FILE* f);

struct ArrayList* parseCSV(char* filename);
