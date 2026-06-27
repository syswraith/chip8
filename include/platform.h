#include <stdbool.h>
#include <stdint.h>

void platform_init(int scale);
void platform_shutdown(void);
bool platform_should_close(void);
void platform_poll_input(void);
void platform_render(int scale);
void platform_update_sound(void);
