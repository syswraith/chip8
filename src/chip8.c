#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../include/chip8.h"
#include "../include/opcode.h"

// initialise the struct here
Chip8 chip = {0};

// initialise the fontset here
uint8_t fontset[80] = {
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

void chip_init() {
  memset(&chip, 0, sizeof(chip));
  chip.pc = 0x200;
  memcpy(&chip.memory[0x50], fontset, sizeof(fontset));
  memset(&chip.keypad[0x0], 0, sizeof(chip.keypad));
}

void dump_keypad() {
  printf("= Dumping keypad\n");

  for (int i = 0; i < 16; i++)
    printf("%02x: %d ", i, chip.keypad[i]);

  printf("\n");
}

void dump_memory() {
  printf("= Dumping memory\n");
  for (int i = 0; i < 4096; i += 2) {
    printf("%03X: %02X %02X\n", i, chip.memory[i], chip.memory[i + 1]);
  }
}

void dump_registers() {
  printf("= Dumping registers\n");
  for (int i = 0; i < 16; i++) {
    printf("V[%02X]: %08X\n", i, chip.v[i]);
  }
  printf("Index: %08X\n", chip.index);
  printf("Sound: %02X\n", chip.sound);
  printf("Delay: %02X\n", chip.delay);

  printf("PC: %02X\n", chip.pc);
  printf("SP: %02X\n", chip.sp);
}

void dump_stack() {
  printf("= Dumping stack\n");
  for (int i = 0; i < 256; i++) {
    printf("%03X: %04X\n", i, chip.stack[i]);
  }
}

bool chip8_cycle(void) {
  if (chip.pc >= 4094)
    return false;

  uint16_t instruction = (chip.memory[chip.pc] << 8) | chip.memory[chip.pc + 1];
  chip.pc += 2;

  if (!fetch_execute(&instruction)) {
    // Unknown opcode — log but keep running
    fprintf(stderr, "Unknown opcode: %04X at PC %03X\n", instruction,
            chip.pc - 2);
  }
  return true; // Only return false on PC overflow
}

void chip8_update_timers(void) {
  if (chip.delay > 0) {
    chip.delay--;
  }

  if (chip.sound > 0) {
    chip.sound--;
  }
}
