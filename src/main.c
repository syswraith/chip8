#include "../include/chip8.h"
#include "../include/memory.h"
#include "../include/platform.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define CLOCK_SPEED 500
#define TARGET_FPS 60

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <path_to_rom> [scale]\n", argv[0]);
    return 1;
  }

  int scale = (argc >= 3) ? atoi(argv[2]) : 10;
  if (scale < 1) {
    scale = 10;
  }

  chip_init();
  load_rom(argv[1]);

  platform_init(scale);

  const double cycle_budget = 1.0 / CLOCK_SPEED;
  double cycle_accumulator = 0.0;

  while (!platform_should_close()) {
    platform_poll_input();
    chip8_update_timers();
    platform_update_sound();

    cycle_accumulator += GetFrameTime();
    while (cycle_accumulator >= cycle_budget) {
      if (!chip8_cycle()) {
        fprintf(stderr, "CPU halted at PC 0x%03X\n", chip.pc);
        platform_shutdown();
        return 1;
      }
      cycle_accumulator -= cycle_budget;
    }

    platform_render(scale);
  }

  platform_shutdown();
  return 0;
}
