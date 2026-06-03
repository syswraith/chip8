#include <stdint.h>

typedef struct {
  uint8_t display[64][32];
  uint8_t memory[4096];
  uint8_t v[16];
  uint8_t sound;
  uint8_t delay;
  uint8_t sp;

  uint16_t pc;
  uint16_t index;
  uint16_t stack[256];
} Chip8;

extern Chip8 chip8;

void chip8_init();
