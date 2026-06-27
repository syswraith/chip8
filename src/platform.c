#include "../include/chip8.h"
#include "../include/platform.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

static const int key_map[16] = {
    KEY_X, KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q, KEY_W, KEY_E, KEY_A,
    KEY_S, KEY_D, KEY_Z, KEY_C, KEY_FOUR, KEY_R, KEY_F, KEY_V,
};

static Sound beep_sound;
static bool audio_ready = false;

static Wave make_beep_wave(void) {
  const unsigned int sample_rate = 44100;
  const unsigned int frame_count = sample_rate / 10;
  short *samples = malloc(frame_count * sizeof(short));

  for (unsigned int i = 0; i < frame_count; i++) {
    float t = (float)i / (float)sample_rate;
    samples[i] = (short)(32767.0f * sinf(2.0f * PI * 440.0f * t));
  }

  Wave wave = {
      .frameCount = frame_count,
      .sampleRate = sample_rate,
      .sampleSize = 16,
      .channels = 1,
      .data = samples,
  };

  return wave;
}

void platform_init(int scale) {
  InitWindow(64 * scale, 32 * scale, "CHIP-8");
  SetTargetFPS(60);

  InitAudioDevice();
  Wave wave = make_beep_wave();
  beep_sound = LoadSoundFromWave(wave);
  free(wave.data);
  audio_ready = true;
}

void platform_shutdown(void) {
  if (audio_ready) {
    UnloadSound(beep_sound);
    CloseAudioDevice();
    audio_ready = false;
  }
  CloseWindow();
}

bool platform_should_close(void) {
  return WindowShouldClose();
}

void platform_poll_input(void) {
  memset(chip.keypad, 0, sizeof(chip.keypad));

  for (int i = 0; i < 16; i++) {
    if (IsKeyDown(key_map[i])) {
      chip.keypad[i] = 1;
    }
  }
}

void platform_render(int scale) {
  BeginDrawing();
  ClearBackground(BLACK);

  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 64; x++) {
      if (chip.display[x][y]) {
        DrawRectangle(x * scale, y * scale, scale, scale, RAYWHITE);
      }
    }
  }

  EndDrawing();
}

void platform_update_sound(void) {
  if (!audio_ready) {
    return;
  }

  if (chip.sound > 0) {
    if (!IsSoundPlaying(beep_sound)) {
      PlaySound(beep_sound);
    }
  } else {
    StopSound(beep_sound);
  }
}
