#include "../include/chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_rom(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open ROM.\n");
        return;
    }

    fread(chip.memory + 0x200,
          1,
          sizeof(chip.memory) - 0x200,
          file);

    fclose(file);

    char video_path[256];
    strcpy(video_path, path);

    char *dot = strrchr(video_path, '.');

    if (dot)
        strcpy(dot, ".vid");
    else
        strcat(video_path, ".vid");

    chip.video = fopen(video_path, "rb");

    if (!chip.video) {
        fprintf(stderr, "Warning: Could not open %s\n", video_path);
    }
}
