#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define size(x) ((sizeof(x)) / (sizeof(x[0])))

typedef struct {
  uint8_t display[64][32];
  uint8_t memory[4096];
  uint8_t keypad[16];
  uint8_t v[16];
  uint8_t sound;
  uint8_t delay;
  uint8_t sp;
  FILE *video;

  uint16_t pc;
  uint16_t index;
  uint16_t stack[256];
} Chip8;

extern Chip8 chip;

void chip_init();
bool chip8_cycle(void);
void chip8_update_timers(void);

void dump_keypad();
void dump_memory();
void dump_registers();
void dump_stack();
