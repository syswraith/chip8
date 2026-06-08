#include "../include/chip8.h"
#include "../include/memory.h"
#include "../include/opcode.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_STEPS 12

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path_to_rom>\n", argv[0]);
        return 1;
    }

    chip_init();
    load_rom(argv[1]);

    printf("--- Executing exactly %d steps ---\n\n", MAX_STEPS);

    for (int step = 1; step <= MAX_STEPS; step++) {
        // Safety check: Prevent running past CHIP-8 RAM boundaries
        if (chip.pc >= 4095) {
            printf("[ERROR] PC out of bounds at Step %d (PC: 0x%03X)\n", step, chip.pc);
            break;
        }

        // Fetch the 16-bit Big-Endian instruction
        uint16_t instruction = (chip.memory[chip.pc] << 8) | chip.memory[chip.pc + 1];

        printf("[Step %02d] PC: 0x%03X | Executing Opcode: %04X\n", step, chip.pc, instruction);

        if (instruction == 0x0000) {
            printf(">> Hit 0x0000 Halt instruction. Stopping early.\n");
            break;
        }

        // Decode and Execute
        fetch(&instruction);

        // Global PC Increment Logic
        uint16_t opcode_type = instruction & 0xF000;
        if (instruction == 0x00EE || opcode_type == 0x1000 || opcode_type == 0x2000) {
            // Jump, Call, and Return change chip.pc themselves. Leave them alone!
        } else {
            // Normal instructions move forward 2 bytes
            chip.pc += 2;
        }
    }

    // Dump state at the very end of our step limit
    printf("\n--- Step Limit Reached. Final State Audit ---\n");
    dump_registers();
    dump_stack();

    return 0;
}
