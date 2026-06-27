#include "../include/chip8.h"
#include "../include/display.h"
#include <stdio.h>
#include <string.h>

void clear_display(void) {
  memset(chip.display, 0, sizeof(chip.display));
}

uint8_t draw_sprite(uint8_t x, uint8_t y, uint8_t height) {
  uint8_t collision = 0;

  for (uint8_t row = 0; row < height; row++) {
    uint8_t sprite_byte = chip.memory[chip.index + row];

    for (uint8_t col = 0; col < 8; col++) {
      if ((sprite_byte & (0x80u >> col)) == 0) {
        continue;
      }

      uint8_t px = (x + col) % 64;
      uint8_t py = (y + row) % 32;

      if (chip.display[px][py]) {
        collision = 1;
      }

      chip.display[px][py] ^= 1;
    }
  }

  return collision;
}

void dump_display(void) {
  printf("= Dumping display\n");

  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 64; x++) {
      putchar(chip.display[x][y] ? '#' : '.');
    }
    putchar('\n');
  }
}
