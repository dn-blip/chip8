#include "chip8.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 0x00 - 0x1FF is interpreter memory
// 0x200 - 0xFFF contains the actual adresses
// 0x050 - 0x0A0 is where we should put the characters

// copied from https://austinmorlan.com/posts/chip8_emulator

const uint8_t fontset[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

/// TODO: RNG, better solutions that static arrays in headers.
int chip8_load_file(const char *filename, struct chip8_t *chip8) {
        const unsigned int start_address = 0x200;
        const unsigned int fontset_address = 0x50;
        if (chip8 == NULL) return -1;
        FILE *fp;
        fp = fopen(filename, "rb");
        if (fp == NULL) return -1;

        // file size
        fseek(fp, SEEK_END, 0L);

        long size = ftell(fp);

        char *buffer = (char *) malloc(size);

        fseek(fp, SEEK_SET, 0L);

        fread(buffer, sizeof(char), size, fp);

        fclose(fp);

        // load buffer into the `chip8`. At last..
        for (long i = 0; i < size; i++) {
                chip8->memory[start_address + i] = buffer[i];
        }
        for (long i = 0; i < 80; i++) {
                chip8->memory[fontset_address + i] = fontset[i];
        }
        chip8->program_counter = start_address;

        free(buffer);
        return 0;
}
