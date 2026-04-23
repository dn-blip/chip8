#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

struct chip8_t {
        // for rng
        uint8_t registers[16];
        uint8_t memory[4096];
        uint16_t index_register;
        uint16_t program_counter;
        uint16_t stack[16];
        time_t curr_time;
};

/// Fills up the `chip8_t` struct with data so you can just plug and play.
/// If failure, chip8 is unmodified and error code of -1 is returned.
int chip8_load_file(const char *filename, struct chip8_t *chip8);

inline size_t _random_byte_gen(struct chip8_t *chip8);
#endif
