#include "../include/opcode.h"
#include "../include/chip8.h"
#include "../include/stack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void get_n(const uint16_t *instruction, uint8_t *n) {
  assert(n);
  *n = (*instruction & 0x00f);
}

void get_nn(const uint16_t *instruction, uint8_t *nn) {
  assert(nn);
  *nn = (*instruction & 0x00ff);
}

void get_nnn(const uint16_t *instruction, uint16_t *nnn) {
  assert(nnn);
  *nnn = (*instruction & 0x0fff);
}

void get_x(const uint16_t *instruction, uint8_t *x) {
  assert(x);
  *x = ((*instruction & 0x0f00) >> 8);
}

void get_xy(const uint16_t *instruction, uint8_t *x, uint8_t *y) {
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

void if_vx_ee_nn(const uint16_t *instruction) {

  uint8_t nn, x;
  get_x(instruction, &x);
  get_nn(instruction, &nn);

  if (chip.v[x] == nn) {
    chip.pc += 2;
  }
}

void if_vx_ne_nn(const uint16_t *instruction) {

  uint8_t nn, x;
  get_x(instruction, &x);
  get_nn(instruction, &nn);

  if (chip.v[x] != nn) {
    chip.pc += 2;
  }
}

void if_vx_ee_vy(const uint16_t *instruction) {

  uint8_t nn, x, y;
  get_xy(instruction, &x, &y);
  get_nn(instruction, &nn);

  if (chip.v[x] == chip.v[y]) {
    chip.pc += 2;
  }
}

void vx_eq_nn(const uint16_t *instruction) {

  uint8_t nn, x;
  get_x(instruction, &x);
  get_nn(instruction, &nn);

  chip.v[x] = nn;
}

void vx_add_eq_nn(const uint16_t *instruction) {

  uint8_t nn, x;
  get_x(instruction, &x);
  get_nn(instruction, &nn);

  chip.v[x] += nn;
}

void vx_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  chip.v[x] = chip.v[y];
}

void vx_add_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  chip.v[x] += chip.v[y];
}

void vx_or_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  chip.v[x] |= chip.v[y];
}
void vx_and_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  chip.v[x] &= chip.v[y];
}

void vx_xor_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  chip.v[x] ^= chip.v[y];
}

void vx_add_eq_vy_carry(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  uint16_t sum = chip.v[x] + chip.v[y];
  uint16_t carry = (sum > 0xff) ? 1 : 0;
  chip.v[x] = sum & 0xff;
  chip.v[0xf] = carry;
}

void vx_sub_eq_vy_borrow(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  uint16_t no_borrow = (chip.v[x] >= chip.v[y]) ? 1 : 0;
  chip.v[x] -= chip.v[y];
  chip.v[0xf] = no_borrow;
}

void vx_shr_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  uint8_t shifted_bit = chip.v[y] & 0x01;
  chip.v[x] = chip.v[y] >> 1;
  chip.v[0xf] = shifted_bit;
}

void vx_rev_sub_eq_vy_borrow(const uint16_t *instruction) {
    uint8_t x, y;
    get_xy(instruction, &x, &y);
    uint8_t no_borrow = (chip.v[y] >= chip.v[x]) ? 1 : 0;
    chip.v[x] = chip.v[y] - chip.v[x];
    chip.v[0xF] = no_borrow;
}

void vx_shl_eq_vy(const uint16_t *instruction) {
  uint8_t x, y;
  get_xy(instruction, &x, &y);

  uint8_t shifted_bit = chip.v[y] >> 7;
  chip.v[x] = chip.v[y] << 1;
  chip.v[0xf] = shifted_bit;
}

void if_vx_ne_vy(const uint16_t *instruction) {

  uint8_t nn, x, y;
  get_xy(instruction, &x, &y);
  get_nn(instruction, &nn);

  if (chip.v[x] != chip.v[y]) {
    chip.pc += 2;
  }
}

void i_eq_nn(const uint16_t *instruction) {
  uint8_t nn;
  get_nn(instruction, &nn);

  chip.index = nn;
}

void jump_nnn(const uint16_t *instruction) {
  uint16_t nnn;
  get_nnn(instruction, &nnn);

  chip.pc = (nnn + chip.v[0x0]);
}

void vx_eq_rand_nn(const uint16_t *instruction) {
    uint8_t x, nn, random_number;
    get_x(instruction, &x);
    get_nn(instruction, &nn);
    random_number = rand() % 256;
    chip.v[x] = random_number & nn;
}


Opcode opcode[] = {
  // pls no separate

  {0xf000, 0x1000, jump},
  {0xf000, 0x2000, subroutine_call},
  {0x00ff, 0x00ee, ret},
  {0xf000, 0x3000, if_vx_ee_nn},
  {0xf000, 0x4000, if_vx_ne_nn}, 
  {0xf000, 0x5000, if_vx_ee_vy},
  {0xf000, 0x6000, vx_eq_nn},
  {0xf000, 0x7000, vx_add_eq_nn},
  {0xf00f, 0x8000, vx_eq_vy},
  {0xf00f, 0x8001, vx_or_eq_vy},
  {0xf00f, 0x8002, vx_and_eq_vy},
  {0xf00f, 0x8003, vx_xor_eq_vy},
  {0xf00f, 0x8004, vx_add_eq_vy_carry},
  {0xf00f, 0x8005, vx_sub_eq_vy_borrow},
  {0xf00f, 0x8006, vx_shr_eq_vy},
  {0xf00f, 0x8007, vx_rev_sub_eq_vy_borrow},
  {0xf00f, 0x800e, vx_shl_eq_vy},
  {0xf00f, 0x9000, if_vx_ne_vy},
  {0xf000, 0xA000, i_eq_nn},
  {0xf000, 0xB000, jump_nnn},
  {0xf000, 0xC000, vx_eq_rand_nn},

  // pls no separate
};

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
