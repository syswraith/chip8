#include <stdint.h>

typedef struct {
  uint16_t mask;
  uint16_t pattern;
  void (*handler)(const uint16_t *instruction);
} Opcode;

// helper functions
void get_n(const uint16_t *instruction, uint16_t *n);
void get_nn(const uint16_t *instruction, uint16_t *nn);
void get_nnn(const uint16_t *instruction, uint16_t *nn);
void get_x(const uint16_t *instruction, uint16_t *x);
void get_xy(const uint16_t *instruction, uint16_t *x, uint16_t *y);

/*
 * General format
 * 0x00ee
 * 0x1nnn
 * 0x2nnn
 * 0x3nnn
 * 0x4nnn
 * 0x5nnn
 * 0x6nnn
 * 0x7nnn
 * 0x8nn0
 * 0x8nn1
 * 0x8nn2
 * 0x8nn3
 */

void ret(const uint16_t *instruction);
void jump(const uint16_t *instruction);
void subroutine_call(const uint16_t *instruction);
void if_vx_ee_nn(const uint16_t *instruction);
void if_vx_ne_nn(const uint16_t *instruction);
void if_vx_ee_vy(const uint16_t *instruction);
void vx_eq_nn(const uint16_t *instruction);
void vx_p_eq_nn(const uint16_t *instruction);
void vx_eq_vy(const uint16_t *instruction);
void vx_p_eq_vy(const uint16_t *instruction);
void vx_or_eq_vy(const uint16_t *instruction);
void vx_and_eq_vy(const uint16_t *instruction);
void vx_xor_eq_vy(const uint16_t *instruction);

void fetch(const uint16_t *instruction);
void decode_and_execute(const uint16_t *instruction, const uint16_t index);
