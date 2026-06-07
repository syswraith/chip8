#include "../include/opcode.h"
#include "../include/chip8.h"
#include "../include/stack.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

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

void jump(const uint16_t *instruction) {
  uint16_t nnn;
  get_nnn(instruction, &nnn);

  printf("Executing jump\n");

  chip.pc = nnn;
}

void subroutine_call(const uint16_t *instruction) {
  uint16_t nnn;
  get_nnn(instruction, &nnn);

  printf("Pushing onto stack and setting pc\n");

  push(chip.pc + 2);
  chip.pc = nnn;
}

void ret(const uint16_t *instruction) {
  (void)instruction;
  printf("Returning to previous address\n");
  chip.pc = pop();
}

Opcode opcode[] = {
    // pls no separate

    {0xf000, 0x1000, jump},
    {0xf000, 0x2000, subroutine_call},
    {0x00ff, 0x00ee, ret}};

void fetch(const uint16_t *instruction) {
  for (uint16_t index = 0; index < size(opcode); index++) {
    decode_and_execute(instruction, index);
  }
};

void decode_and_execute(const uint16_t *instruction, const uint16_t index) {
  if ((*instruction & opcode[index].mask) == opcode[index].pattern) {
    printf("Matched with pattern: %02X\n", opcode[index].pattern);
    opcode[index].handler(instruction);
    return;
  }
};
