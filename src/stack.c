#include "../include/chip8.h"
#include <stdint.h>
#include <stdio.h>

void push(uint16_t element) {
  chip.stack[chip.sp++] = element;
}

uint16_t pop() {
  if (chip.sp == 0) {
    fprintf(stderr, "Stack underflow!\n");
    return 0;
  }
  return chip.stack[--chip.sp];
}
