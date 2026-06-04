#include "../include/opcode.h"
#include <assert.h>
#include <stdint.h>

Opcode opcode[] = {};

void get_n(const uint16_t *instruction, uint16_t *n) {
  assert(n);
  *n = (*instruction & 0x00f);
}

void get_nn(const uint16_t *instruction, uint16_t *nn) {
  assert(nn);
  *nn = (*instruction & 0x00ff);
}

void get_nnn(const uint16_t *instruction, uint16_t *nn) {
  assert(nn);
  *nn = (*instruction & 0x0fff);
}

void get_x(const uint16_t *instruction, uint16_t *x) {
  assert(x);
  *x = ((*instruction & 0x0f00) >> 8);
}

void get_xy(const uint16_t *instruction, uint16_t *x, uint16_t *y) {
  assert(x);
  assert(y);
  *x = ((*instruction & 0x0f00) >> 8);
  *y = ((*instruction & 0x00f0) >> 4);
}
