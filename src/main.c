#include "../include/chip8.h"
#include "../include/memory.h"
#include "../include/opcode.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
  (void)argc;

  chip_init();
  load_rom(argv[1]);

  while (1) {
    uint16_t instruction =
        (chip.memory[chip.pc] << 8) | chip.memory[chip.pc + 1];

    printf("Executing %04X\n", instruction);
    if (instruction == 0x0000) {
      break;
    }

    fetch(&instruction);
  }

  return 0;
}
