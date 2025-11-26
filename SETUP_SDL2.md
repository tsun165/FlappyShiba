# SDL2 Setup Guide for FlappyShiba

This guide provides detailed instructions for setting up SDL2 libraries for the FlappyShiba project.

## Quick Setup

### 1. Download SDL2 Libraries

Download the following **VC (Visual C++)** development packages:

| Library | Download Link | Version |
|---------|---------------|---------|
| SDL2 | https://github.com/libsdl-org/SDL/releases/download/release-2.32.8/SDL2-devel-2.32.8-VC.zip | Latest 2.x |
| SDL2_image | https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.8-VC.zip | Latest 2.x |
| SDL2_ttf | https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.24.0-VC.zip | Latest 2.x |
| SDL2_mixer | https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.8.1-VC.zip | Latest 2.x |

**Important:** Make sure to download the `-devel-*-VC.zip` files (NOT the runtime-only versions).

### 2. Extract and Organize

After downloading all four libraries:

1. Create the directory structure:
```
FlappyShiba/
└── external/
    └── SDL2/
        ├── include/
        └── lib/
            └── x64/
```

2. **For each library** (SDL2, SDL2_image, SDL2_ttf, SDL2_mixer):
   - Extract the zip file
   - Copy all `.h` files from `[library]/include/` → `FlappyShiba/external/SDL2/include/`
   - Copy all `.lib` files from `[library]/lib/x64/` → `FlappyShiba/external/SDL2/lib/x64/`
   - Copy all `.dll` files from `[library]/lib/x64/` → `FlappyShiba/external/SDL2/lib/x64/`

### 3. Verify File Structure

After setup, your `external/SDL2/` folder should contain:

```
external/SDL2/
├── include/
│   ├── SDL.h
│   ├── SDL_main.h
│   ├── SDL_image.h
│   ├── SDL_ttf.h
│   ├── SDL_mixer.h
│   └── ... (50+ other SDL headers)
└── lib/
    └── x64/
        ├── SDL2.lib
        ├── SDL2main.lib
        ├── SDL2_image.lib
        ├── SDL2_ttf.lib
        ├── SDL2_mixer.lib
        ├── SDL2.dll
        ├── SDL2_image.dll
        ├── SDL2_ttf.dll
        ├── SDL2_mixer.dll
        ├── libpng16-16.dll
        ├── zlib1.dll
        ├── libfreetype-6.dll
        └── ... (other dependency DLLs)
```

### 4. Copy DLLs to Build Directory

After building the project for the first time:

1. Navigate to `x64/Debug/` (or `x64/Release/`)
2. Copy **all `.dll` files** from `external/SDL2/lib/x64/` to this directory
3. The executable needs these DLLs at runtime

You can automate this with a post-build event in Visual Studio:

**Project Properties → Build Events → Post-Build Event → Command Line:**
```cmd
xcopy /y /d "$(ProjectDir)external\SDL2\lib\x64\*.dll" "$(OutDir)"
```

## Detailed File List

### Required Header Files (.h)
- SDL.h, SDL_main.h (core SDL2)
- SDL_image.h (image loading: PNG, JPG, etc.)
- SDL_ttf.h (TrueType font rendering)
- SDL_mixer.h (audio mixing and music)

### Required Library Files (.lib)
- SDL2.lib, SDL2main.lib
- SDL2_image.lib
- SDL2_ttf.lib
- SDL2_mixer.lib

### Required Runtime DLLs (.dll)

**Core SDL2:**
- SDL2.dll

**SDL2_image:**
- SDL2_image.dll
- libpng16-16.dll (PNG support)
- zlib1.dll (compression)

**SDL2_ttf:**
- SDL2_ttf.dll
- libfreetype-6.dll (font rendering)

**SDL2_mixer:**
- SDL2_mixer.dll
- libmpg123-0.dll (MP3 support, optional)
- libogg-0.dll (OGG support, optional)
- libvorbis-0.dll (OGG Vorbis support, optional)
- libvorbisfile-3.dll (OGG Vorbis file support, optional)

**Note:** Some dependency DLLs may vary depending on the SDL2 version you download.

## Troubleshooting

### "Cannot open include file: 'SDL.h'"

**Solution:**
- Verify `external/SDL2/include/SDL.h` exists
- Check Project Properties → C/C++ → General → Additional Include Directories
- Should contain: `$(ProjectDir)external\SDL2\include`

### "LNK2019: unresolved external symbol" errors

**Solution:**
- Verify `.lib` files are in `external/SDL2/lib/x64/`
- Check Project Properties → Linker → General → Additional Library Directories
- Should contain: `$(ProjectDir)external\SDL2\lib\x64`
- Check Project Properties → Linker → Input → Additional Dependencies
- Should contain: `SDL2.lib;SDL2main.lib;SDL2_image.lib;SDL2_ttf.lib;SDL2_mixer.lib;`

### "The program can't start because SDL2.dll is missing"

**Solution:**
- Copy all `.dll` files from `external/SDL2/lib/x64/` to the same folder as your `.exe`
- Typically `x64/Debug/` or `x64/Release/`

### Wrong SDL version (SDL3 instead of SDL2)

**Symptoms:**
- `TTF_RenderText_Solid` takes wrong number of arguments
- Strange compilation errors in SDL headers

**Solution:**
- Delete all files in `external/SDL2/`
- Download SDL **2.x** versions (NOT 3.x)
- Re-extract and organize as described above

## Alternative: Using vcpkg

If you prefer a package manager approach:

```cmd
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install SDL2 libraries
.\vcpkg install sdl2:x64-windows
.\vcpkg install sdl2-image:x64-windows
.\vcpkg install sdl2-ttf:x64-windows
.\vcpkg install sdl2-mixer:x64-windows

# Integrate with Visual Studio
.\vcpkg integrate install
```

Then the libraries will be automatically available in all VS projects.

## Notes

- The `external/SDL2/` folder is **excluded from git** via `.gitignore`
- Each developer must download and setup SDL2 independently
- This keeps the repository size small and avoids licensing issues
- Make sure to use the **x64** versions if building for 64-bit (recommended)
- Use **x86** versions if building for 32-bit (Win32 platform)

## Support

If you encounter issues not covered here:
1. Check the [official SDL2 documentation](https://wiki.libsdl.org/)
2. Verify you're using SDL2 (version 2.x.x), not SDL1 or SDL3
3. Make sure all paths in Project Properties use `$(ProjectDir)` for portability
4. Open an issue in this repository with your error message

