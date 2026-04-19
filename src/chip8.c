#include "chip8.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 0x00 - 0x1FF is interpreter memory
// 0x200 - 0xFFF contains the actual adresses
// 0x050 - 0x0A0 is where we should put the characters

/// TODO: RNG, better solutions that static arrays in headers.
int chip8_load_file(const char *filename, struct chip8_t *chip8) {
        // error values and other constants
        int seek_result;
        int read_result;
        const unsigned int start_address = 0x200;
        const unsigned int fontset_address = 0x50;
        if (chip8 == NULL) return -1;
        FILE *fp;
        fp = fopen(filename, "rb");
        if (fp == NULL) return -1;

        // file size
        seek_result = fseek(fp, SEEK_END, 0L);
        if (seek_result != 0) return -1;

        long size = ftell(fp);

        char *buffer = (char *) malloc(size);

        seek_result = fseek(fp, SEEK_SET, 0L);
        if (seek_result != 0) return -1;

        read_result = fread(buffer, sizeof(char), size, fp);
        if (read_result != size) return -1;

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
