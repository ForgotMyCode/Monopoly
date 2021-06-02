#pragma once

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(arr) (sizeof((arr)) / sizeof(*(arr)))
#endif