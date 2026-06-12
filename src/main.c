#include "../include/chip8.h"
#include "../include/memory.h"
#include "../include/opcode.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_STEPS 64

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path_to_rom>\n", argv[0]);
        return 1;
    }

    chip_init();
    load_rom(argv[1]);

    for (int step = 1; step <= MAX_STEPS; step++) {
        if (chip.pc >= 4094) {
            printf("[ERROR] PC out of bounds at step %d (PC: 0x%03X)\n", step, chip.pc);
            break;
        }

        uint16_t instruction = (chip.memory[chip.pc] << 8) | chip.memory[chip.pc + 1];

        if (instruction == 0x0000) {
            printf("[HALT] PC: 0x%03X — empty instruction, stopping.\n", chip.pc);
            break;
        }

        printf("[Step %02d] PC: 0x%03X | Opcode: %04X\n", step, chip.pc, instruction);

        uint16_t pc_before = chip.pc;

        // Always advance PC before executing.
        // Skip/jump/call/ret handlers then add their own offset on top.
        chip.pc += 2;

        fetch(&instruction);

        // Self-jump: PC ended up where it started — treat as halt.
        if (chip.pc == pc_before) {
            printf("[HALT] PC: 0x%03X — self-jump detected, stopping.\n", chip.pc);
            break;
        }
    }

    printf("\n");
    dump_registers();
    return 0;
}
