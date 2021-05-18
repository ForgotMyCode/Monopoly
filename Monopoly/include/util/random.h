#pragma once

#include <stdint.h>

#define PRNG_STATES_COUNT 3

#define PRNG_DICE 0

void seed_prng_state(uint8_t prng_id, uint32_t value);

uint32_t xorshift32(uint32_t state);

uint32_t next_random_int(uint8_t prng_id);