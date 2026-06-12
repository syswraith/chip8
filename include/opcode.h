#include <stdint.h>

typedef struct {
  uint16_t mask;
  uint16_t pattern;
  void (*handler)(const uint16_t *instruction);
} Opcode;

// helper functions
void get_n(const uint16_t *instruction, uint8_t *n);
void get_nn(const uint16_t *instruction, uint8_t *nn);
void get_nnn(const uint16_t *instruction, uint16_t *nnn);
void get_x(const uint16_t *instruction, uint8_t *x);
void get_xy(const uint16_t *instruction, uint8_t *x, uint8_t *y);

void ret(const uint16_t *instruction);
void jump(const uint16_t *instruction);
void subroutine_call(const uint16_t *instruction);
void if_vx_ee_nn(const uint16_t *instruction);
void if_vx_ne_nn(const uint16_t *instruction);
void if_vx_ee_vy(const uint16_t *instruction);
void vx_eq_nn(const uint16_t *instruction);
void vx_add_eq_nn(const uint16_t *instruction);
void vx_eq_vy(const uint16_t *instruction);
void vx_add_eq_vy(const uint16_t *instruction);
void vx_or_eq_vy(const uint16_t *instruction);
void vx_and_eq_vy(const uint16_t *instruction);
void vx_xor_eq_vy(const uint16_t *instruction);
void vx_add_eq_vy_carry(const uint16_t *instruction);
void vx_sub_eq_vy_borrow(const uint16_t *instruction);
void vx_shr_eq_vy(const uint16_t *instruction);
void vx_rev_sub_eq_vy_borrow(const uint16_t *instruction);
void vx_shl_eq_vy(const uint16_t *instruction);
void i_eq_nnn(const uint16_t *instruction);
void jump_nnn(const uint16_t *instruction);
void vx_eq_rand_nn(const uint16_t *instruction);
void if_vx_not_pressed(const uint16_t *instruction);
void if_vx_pressed(const uint16_t *instruction);
void vx_eq_delay(const uint16_t *instruction);
void delay_eq_vx(const uint16_t *instruction);
void sound_eq_vx(const uint16_t *instruction);
void save_into_v0_to_vx(const uint16_t *instruction);
void read_into_v0_to_vx(const uint16_t *instruction);

void fetch(const uint16_t *instruction);
int decode_and_execute(const uint16_t *instruction, const uint16_t index);
