#include "../include/chip8.h"
#include "../include/memory.h"

int main(int argc, char **argv) {
  (void)argc;

  chip_init();
  load_rom(argv[1]);
  dump_memory();
  dump_registers();
  dump_stack();

  return 0;
}
