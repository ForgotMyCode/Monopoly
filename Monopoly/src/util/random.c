#include <util/random.h>

uint32_t prng_states[PRNG_STATES_COUNT];

void seed_prng_state(uint8_t prng_id, uint32_t value) {
    prng_states[prng_id] = value;
}

uint32_t xorshift32(uint32_t state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

uint32_t next_random_int(uint8_t prng_id) {
    uint32_t state = xorshift32(prng_states[prng_id]);
    prng_states[prng_id] = state;
    return state >> 1;
}