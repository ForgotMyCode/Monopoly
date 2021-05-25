#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <core.h>
#include <util/arraylist.h>

void readInt(int* n);

void freadLong(long* n, FILE* f);

ArrayList* parseCSV(char* filename);

void initializePrng();
