#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>

// State for the PRNG
static uint32_t seed = 1; // Initial seed value

// Function to seed the PRNG
static inline void srand(uint32_t s) {
    seed = s;
}

// Function to generate a pseudo-random number using the LCG algorithm
static inline int rand() {
    seed = (1103515245 * seed + 12345) % 0x80000000;
    return (int)(seed & 0x7FFFFFFF);
}

// Function to set a block of memory to a specified value
static inline void *memset(void *s, int c, unsigned long n) {
    unsigned char *p = (unsigned char *)s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}
// Función para leer el Time Stamp Counter
static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

// usleep using rdtsc
void usleep(uint64_t microseconds) {
	uint16_t cpu_speed = *(uint16_t *)(0x5010);
    uint64_t cpu_frequency_hz = 3000000000;
    uint64_t cycles_to_wait = (cpu_frequency_hz / 1000000) * microseconds;

    uint64_t start = rdtsc();
    while ((rdtsc() - start) < cycles_to_wait) {
        // (busy-wait)
    }
}

#endif