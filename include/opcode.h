#include <stdint.h>

typedef struct {
  uint16_t mask;
  uint16_t pattern;
  void (*handler)(uint16_t instruction);
} Opcode;

void get_n(const uint16_t *instruction, uint16_t *n);
void get_nn(const uint16_t *instruction, uint16_t *nn);
void get_nnn(const uint16_t *instruction, uint16_t *nn);
void get_x(const uint16_t *instruction, uint16_t *x);
void get_xy(const uint16_t *instruction, uint16_t *x, uint16_t *y);
