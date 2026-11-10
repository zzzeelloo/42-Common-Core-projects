[← Back to 42 Common Core](../README.md)

*This project has been created as part of the 42 curriculum by anpetit, zcherif.*

# cub3D

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![MiniLibX](https://img.shields.io/badge/MiniLibX-Graphics-green)](https://github.com/42Paris/minilibx-linux)

A 3D maze explorer built in C using raycasting, inspired by the legendary Wolfenstein 3D. Navigate through a textured labyrinth rendered in real-time using the MiniLibX graphics library.

## Description

cub3D is a graphical project from the 42 cursus that introduces the technique of **raycasting** to create a dynamic first-person perspective inside a maze. The engine casts one ray per screen column, calculates wall distances to determine their height, and applies directional textures (North, South, East, West) to create the illusion of 3D from a 2D map.

The program reads a `.cub` scene description file that defines wall textures, floor/ceiling colors, and the map layout. It then validates the map (enclosed by walls, single player, valid characters, flood fill enclosure check) before launching the graphical window.

### Raycasting Engine

For each vertical column of the screen:

1. **Ray angle** — computed from the player angle and FOV across the screen width
2. **DDA (Digital Differential Analysis)** — steps through the grid to find the first wall hit
3. **Distance correction** — perpendicular distance with fisheye compensation via `cos(ray_angle - player_angle)`
4. **Textured rendering** — wall slice height and texture column determined by hit face (N/S/E/W)
5. **Background** — ceiling and floor filled with the configured RGB colors

### Map Parsing

The `.cub` file is fully validated before rendering:
- **Textures**: 4 wall textures (NO, SO, WE, EA) as XPM files
- **Colors**: RGB values for floor (`F`) and ceiling (`C`) in range [0,255]
- **Map**: composed of `0` (empty), `1` (wall), `N`/`S`/`E`/`W` (player start + orientation)
- **Enclosure**: a recursive flood fill on a padded grid verifies all walkable areas are enclosed by walls
- **Validation**: duplicate textures/colors, missing config, invalid characters, empty lines in map, content after map — all rejected with explicit error messages

Example `.cub` file:
```
SO ./textures/brick.xpm
WE ./textures/support.xpm
NO ./textures/hedge.xpm
EA ./textures/light.xpm

C 153,204,255
F 96,96,96

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        100100000000000000W000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
1100000111010101111101111000111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Instructions

### Prerequisites

- A C compiler (`cc` / `gcc` / `clang`)
- `make`

**macOS**: No extra dependencies needed (uses AppKit and OpenGL frameworks).

**Linux**:
```bash
sudo apt-get install libxext-dev libx11-dev libbsd-dev
```

### Compilation

```bash
make
```

The Makefile auto-detects the OS and selects the appropriate MiniLibX (macOS or Linux). It compiles MiniLibX first, then links everything together. Supports `all`, `clean`, `fclean`, `re`.

All source files are compiled with `-Wall -Wextra -Werror`.

### Usage

```bash
./cub3D <map.cub>
```

### Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Quit the game |

Multiple keys can be held simultaneously for diagonal movement.

## Project Structure

```
cub3D/
├── Makefile
├── main.c
├── includes/
│   ├── cub3d.h              # Structures, constants, key definitions
│   └── src.h                # Function prototypes
├── src/
│   ├── config/
│   │   ├── error_handler.c       # Error message output
│   │   ├── free_src.c            # Free textures, map, images, MLX resources
│   │   ├── inittial_settings.c   # Init game struct (zero all pointers)
│   │   └── initial_config_settings.c  # Init config and texture structs
│   ├── parsing/
│   │   ├── parse_file.c          # Main parsing pipeline
│   │   ├── buffer.c              # File reading into line buffer
│   │   ├── textures_path.c       # NO/SO/WE/EA texture path extraction
│   │   ├── textures_data.c       # XPM texture loading via MLX
│   │   ├── colors.c              # F/C RGB color parsing and validation
│   │   ├── parse_map.c           # Map dimensions, grid construction
│   │   ├── validate_map.c        # Character check, player count, flood fill
│   │   ├── validate_map_empty_line.c  # Empty line detection within map
│   │   ├── grid_padded.c         # Padded grid for flood fill border
│   │   └── player_data.c         # Player position and angle from map
│   ├── rendering/
│   │   ├── render.c              # Frame loop, pixel put with bounds check
│   │   ├── background.c          # Ceiling and floor painting
│   │   ├── walls.c               # Raycasting loop, distance and height calc
│   │   ├── dda.c                 # DDA algorithm (ray stepping through grid)
│   │   └── texturized_wall.c     # Texture selection and column drawing
│   ├── events/
│   │   ├── keys.c                # Key press/release state management
│   │   ├── moves.c               # Rotation and movement vector calculation
│   │   ├── make_move.c           # Collision detection with wall sliding
│   │   └── closing.c             # Window close and game exit
│   └── utils/
│       ├── get_next_line.c       # GNL (line-by-line file reading)
│       ├── ft_split.c            # String splitting by delimiter
│       ├── ft_atoi.c             # String to int with overflow protection
│       ├── ft_strjoin.c          # String concatenation (frees s1)
│       ├── ft_substr.c           # Substring extraction
│       ├── ft_strdup.c           # String duplication
│       ├── ft_strcmp.c            # String comparison
│       ├── ft_strncmp.c          # String comparison (n bytes)
│       ├── ft_strlcpy.c          # Safe string copy
│       ├── ft_strlen.c           # String length
│       ├── ft_isdigit.c          # Digit check
│       ├── ft_isspace.c          # Whitespace check
│       └── free_array.c          # Free NULL-terminated string array
├── textures/                     # XPM wall texture files
├── maps/                         # .cub scene files (valid and test maps)
└── minilibx/
    ├── macos/                    # MiniLibX for macOS
    └── linux/                    # MiniLibX for Linux
```

## Code Standards

- **42 Norm** — Strict coding standards enforced by norminette
- **Memory Safety** — All images, textures, windows, and allocated memory properly freed on exit. Pointers set to NULL after free to prevent double-free.
- **Error Handling** — Invalid maps, missing textures, bad RGB values, unclosed maps, duplicate configs, wrong file extensions — all caught with explicit error messages on stderr
- **Cross-platform** — Compiles and runs on both macOS and Linux

## Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — Reference for understanding and implementing a raycaster
- [Wolfenstein 3D (1992)](https://en.wikipedia.org/wiki/Wolfenstein_3D) — The original game that pioneered raycasting
- [42 MiniLibX Linux](https://github.com/42Paris/minilibx-linux) — Official MiniLibX repository
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — Community reference for MiniLibX functions

### AI Usage

AI tools were used as a learning aid to understand the mathematical concepts behind the rendering engine: raycasting principles, the DDA (Digital Differential Analysis) algorithm, fisheye correction, perpendicular wall distance calculation, and texture mapping coordinates. AI was not used to generate the source code of the project.
