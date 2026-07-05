# CHIP-8 Project Layout

```text
chip8/
├── roms/
├── include/
│   ├── chip8.h
│   ├── opcode.h
│   ├── memory.h
│   ├── stack.h
│   └── display.h
└── src/
    ├── main.c
    ├── chip8.c
    ├── opcode.c
    ├── memory.c
    ├── stack.c
    ├── display.c
    └── platform.c
```

---

# include/chip8.h

Contains the core CHIP-8 state definition.

### Contents

- `Chip8` struct
- `extern Chip8 chip`
- Constants:
  - Screen width
  - Screen height
  - Memory size
  - Register count
- `chip8_init()` declaration

### Owns

- Memory
- Registers
- Stack
- Timers
- Display buffer
- Program counter
- Index register

---

# src/chip8.c

Contains emulator initialization.

### Contents

- Global CHIP-8 instance

```c
Chip8 chip = {0};
```

- Fontset array

```c
uint8_t fontset[80];
```

- Initialization function

```c
void chip8_init(void);
```

### Responsibilities

- Reset emulator state
- Set PC to `0x200`
- Load fontset into memory
- Clear display
- Clear registers
- Clear stack

---

# include/memory.h

### Declarations

```c
void load_rom(const char *path);
```

---

# src/memory.c

Contains ROM loading code.

### Contents

- File reading
- ROM validation
- Copying ROM into memory

### Responsibilities

- Open ROM
- Read bytes
- Load ROM at address `0x200`

### Code moved here

- `fopen`
- `fread`
- `fclose`

from your ROM reader program.

---

# include/stack.h

### Declarations

```c
void push(uint16_t value);
uint16_t pop(void);
```

---

# src/stack.c

Contains stack operations.

### Contents

```c
push()
pop()
```

### Responsibilities

- Push return addresses
- Pop return addresses
- Update stack pointer

### Used by

- CALL instruction
- RETURN instruction

---

# include/display.h

### Declarations

```c
void clear_display(void);

void draw_sprite(
    uint16_t address,
    int x,
    int y,
    int height
);

void render_display(int scale);
```

---

# src/display.c

Contains display buffer logic.

### Contents

- Clear screen
- Sprite drawing
- XOR rendering
- Collision detection

### Code moved here

```c
testDrawSprite()
```

renamed to

```c
draw_sprite()
```

### Responsibilities

- Handle CHIP-8 graphics instructions
- Modify display buffer

### Does NOT

- Open windows
- Draw Raylib rectangles

---

# include/opcode.h

Contains opcode definitions.

### Contents

```c
typedef struct {
    uint16_t mask;
    uint16_t pattern;
    void (*handler)(uint16_t instruction);
} Opcode;
```

### Declarations

Opcode handlers:

```c
void jmp(uint16_t instruction);
void call(uint16_t instruction);
void vx_ne_nn(uint16_t instruction);
```

Instruction decoding helpers:

```c
get_x()
get_xy()
get_n()
get_nn()
get_nnn()
```

Opcode execution:

```c
void execute(uint16_t instruction);
```

---

# src/opcode.c

Contains CPU instruction implementation.

### Contents

Opcode table:

```c
Opcode opcode[];
```

Dispatch logic:

```c
execute()
```

Decode helpers:

```c
get_x()
get_xy()
get_n()
get_nn()
get_nnn()
```

Opcode handlers:

```c
jmp()
call()
vx_ne_nn()
...
```

### Responsibilities

- Decode instructions
- Execute instructions
- Modify CHIP-8 state

### Code moved here

Your opcode matching example:

```c
if ((instruction & opcode[j].mask)
      == opcode[j].pattern)
{
    opcode[j].handler(instruction);
}
```

---

# src/platform.c

Contains Raylib-specific code.

### Contents

- Window creation
- Drawing rectangles
- Frame timing
- Keyboard polling

### Responsibilities

Convert:

```text
CHIP-8 display buffer
```

into

```text
Raylib window
```

### Code moved here

```c
InitWindow()
BeginDrawing()
DrawRectangle()
EndDrawing()
CloseWindow()
```

---

# src/main.c

Program entry point.

### Responsibilities

1. Initialize emulator
2. Load ROM
3. Create window
4. Run emulation loop

### Final structure

```c
int main(int argc, char **argv)
{
    chip8_init();

    load_rom(argv[1]);

    while (!WindowShouldClose())
    {
        fetch();
        decode();
        execute();

        render_display();
    }

    return 0;
}
```

### Should NOT contain

- Opcode implementations
- Sprite drawing code
- ROM loading code
- Stack code
- Fontset data

Only high-level orchestration.

---

# Data Ownership

```text
chip8.c
│
├── memory[4096]
├── V[16]
├── stack[]
├── display[][]
├── pc
├── index
├── delay timer
└── sound timer

memory.c
└── loads ROM into memory

stack.c
└── manipulates stack

display.c
└── manipulates display buffer

opcode.c
└── manipulates everything through instructions

platform.c
└── shows display buffer on screen

main.c
└── ties everything together
```
