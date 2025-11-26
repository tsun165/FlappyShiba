# FlappyShiba

A Flappy Bird clone with Japanese-inspired aesthetics, featuring a cute Shiba Inu character.

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Setup Instructions](#setup)
5. [How to Play](#play)
6. [Project Structure](#structure)

## Introduction <a name="introduction"></a>

* The game is inspired by Japan-vibe and [Flappy Bird](https://wikipedia.org/wiki/Flappy_Bird) - the famous Vietnamese game developed by Nguyen Ha Dong in 2013.
* Flappy Shiba was created using [SDL2](https://www.libsdl.org/download-2.0.php) and C++ with Visual Studio 2019.

## Features <a name="features"></a>

**1. GameWindow**
* Handles collisions between characters and pipes, the ground, and borders.
* Handles the player's key actions (SPACE to jump).
* Display score and game status.
* Moving background and characters for realistic gameplay.
* Frame rate management for smooth gameplay across different devices.

**2. Game States**
* Start screen with instructions
* Playing state with score tracking
* Game over screen with final score
* Restart functionality

**3. Audio & Graphics**
* Background music and sound effects
* Custom Japanese-themed pixel art sprites
* Smooth animations

## Requirements <a name="requirements"></a>

- **Visual Studio 2019** (or later) with C++ development tools
- **Windows 10/11**
- **SDL2 libraries** (instructions below)

## Setup Instructions <a name="setup"></a>

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/FlappyShiba.git
cd FlappyShiba
```

### 2. Download SDL2 Libraries

You need to download the following SDL2 development libraries (VC version):

1. **SDL2** - [Download SDL2-devel-x.x.x-VC.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-VC.zip)
2. **SDL2_image** - [Download SDL2_image-devel-x.x.x-VC.zip](https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.8-VC.zip)
3. **SDL2_ttf** - [Download SDL2_ttf-devel-x.x.x-VC.zip](https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.24.0-VC.zip)
4. **SDL2_mixer** - [Download SDL2_mixer-devel-x.x.x-VC.zip](https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.8.1-VC.zip)

### 3. Setup SDL2 in Project

After downloading, extract each library and organize them as follows:

```
FlappyShiba/
├── external/
│   └── SDL2/
│       ├── include/
│       │   ├── SDL.h
│       │   ├── SDL_image.h
│       │   ├── SDL_ttf.h
│       │   ├── SDL_mixer.h
│       │   └── ... (other SDL headers)
│       └── lib/
│           └── x64/
│               ├── SDL2.lib
│               ├── SDL2main.lib
│               ├── SDL2_image.lib
│               ├── SDL2_ttf.lib
│               ├── SDL2_mixer.lib
│               ├── SDL2.dll
│               ├── SDL2_image.dll
│               ├── SDL2_ttf.dll
│               ├── SDL2_mixer.dll
│               └── ... (dependency DLLs: libpng16-16.dll, zlib1.dll, etc.)
```

**Steps:**
- Create `external/SDL2/include/` and `external/SDL2/lib/x64/` folders in the project root
- Copy all `.h` files from each SDL2 library's `include/` folder into `external/SDL2/include/`
- Copy all `.lib` and `.dll` files from each SDL2 library's `lib/x64/` folder into `external/SDL2/lib/x64/`

### 4. Open Solution in Visual Studio

1. Open `FlappyShiba.sln` with Visual Studio 2019
2. Select **x64** platform and **Debug** configuration from the toolbar
3. The project is already configured to use:
   - Include directories: `$(ProjectDir)include` and `$(ProjectDir)external\SDL2\include`
   - Library directories: `$(ProjectDir)external\SDL2\lib\x64`
   - Working directory: `$(ProjectDir)`

### 5. Copy DLLs to Output Directory

After building, copy all `.dll` files from `external/SDL2/lib/x64/` to `x64/Debug/`:

```
x64/Debug/
├── FlappyShiba.exe
├── SDL2.dll
├── SDL2_image.dll
├── SDL2_ttf.dll
├── SDL2_mixer.dll
└── ... (other dependency DLLs)
```

### 6. Build and Run

1. Press `Ctrl+Shift+B` to build the solution
2. Press `F5` to run the game
3. Enjoy!

## How to Play <a name="play"></a>

* Press **SPACE** to make the Shiba jump
* Avoid hitting the pipes and the ground
* Try to get the highest score possible!
* Press **SPACE** on game over screen to restart

## Project Structure <a name="structure"></a>

```
FlappyShiba/
├── src/                      # Source files (.cpp)
│   ├── main.cpp
│   ├── GameLoop.cpp
│   ├── Player.cpp
│   ├── Pipe.cpp
│   ├── Background.cpp
│   ├── Sound.cpp
│   └── ...
├── include/                  # Header files (.h)
│   ├── GameLoop.h
│   ├── Player.h
│   ├── Pipe.h
│   └── ...
├── asset/                    # Game assets
│   ├── image/               # Sprites and graphics
│   ├── font/                # TTF fonts
│   ├── sound/               # Sound effects and music
│   ├── data/                # Game data (best score, etc.)
│   ├── medal/               # Medal images
│   └── number/              # Number sprites
├── external/                 # External libraries (SDL2)
│   └── SDL2/
├── x64/Debug/               # Build output (generated)
├── FlappyShiba.sln          # Visual Studio solution
├── FlappyShiba.vcxproj      # Visual Studio project
└── README.md                # This file
```

## Troubleshooting

### "Cannot open include file: 'SDL.h'" or similar errors
- Make sure you've downloaded and placed SDL2 libraries in `external/SDL2/` correctly
- Verify the include paths in Project Properties

### "The program can't start because SDL2.dll is missing"
- Copy all `.dll` files from `external/SDL2/lib/x64/` to the same folder as your `.exe` file

### Game doesn't load images/fonts/sounds
- Ensure Working Directory is set to `$(ProjectDir)` in Project Properties → Debugging
- Check that `asset/` folder is in the project root directory

### Build errors about `to_string` or `TTF_RenderText_Solid`
- Make sure you're using SDL2 (not SDL3)
- Verify `#include <string>` is present in GameLoop.cpp

## Credits

- Original Flappy Bird concept by Nguyen Ha Dong
- SDL2 library by Sam Lantinga and contributors
- Game assets and implementation by [Your Name]

## License

This project is for educational purposes. All rights to the original Flappy Bird concept belong to Nguyen Ha Dong.
