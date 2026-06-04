#include "../include/chip8.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void load_rom(const char *path) {
  FILE *file = fopen(path, "rb");

  if (file == NULL) {
    fprintf(stderr, "Error: Could not open file.\n");
    return;
  }

  fread(chip.memory + 0x200, sizeof(char), sizeof(chip.memory), file);

  fclose(file);
}
