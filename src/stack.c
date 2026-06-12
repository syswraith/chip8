#include "../include/chip8.h"
#include <stdint.h>
#include <stdio.h>

void push(uint16_t element) {
  chip.stack[chip.sp++] = element;
  printf("pushing %x onto the stack\n", element);
}

uint16_t pop() {
  if (chip.sp == 0) {
    fprintf(stderr, "Stack underflow!\n");
    return 0;
  }
  uint16_t address = chip.stack[--chip.sp];
  printf("Popping %x from stack\n", address);
  return address;
}
