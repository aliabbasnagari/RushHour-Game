# RushHour Game

RushHour Semester-1 Project

![DEMO](https://raw.githubusercontent.com/aliabbasnagari/RushHour-Game/refs/heads/master/demo/gameplay.gif)

![Watch the Video](https://github.com/aliabbasnagari/RushHour-Game/raw/refs/heads/master/demo/gameplay.mp4)

## Description

Rush Hour is a game where player has to drive taxi and earn points by picking and dropping passengers at their destinations.

## Building

The game needs OpenGL, FreeGLUT, and GLEW. Install the dev packages for your platform, then build with CMake (wrapped by the included `Makefile`).

### 1. Install dependencies

- **Linux (Debian/Ubuntu):**
  ```
  sudo apt install freeglut3-dev libglew-dev cmake build-essential
  ```
- **macOS (Homebrew):**
  ```
  brew install freeglut glew cmake
  ```
- **Windows:** install [CMake](https://cmake.org/download/) and a compiler (Visual Studio or MinGW), plus FreeGLUT and GLEW (e.g. via [vcpkg](https://github.com/microsoft/vcpkg)). The repo already ships `freeglut.dll` and `glew32.dll` for runtime.

### 2. Build and run

```
make run
```

This runs CMake under the hood (`cmake -S . -B build` + `cmake --build build`) and launches the resulting `Rushhour` executable. Other targets:

- `make build` — configure and compile only.
- `make clean` — remove the `build/` directory.

## How to Play

Use the arrow keys to control your taxi and avoid obstacles as you make your way through the city. Follow the on-screen prompts to pick up and drop off passengers at their designated locations and earn points for completing each task successfully.

If you have any issues with compiling or running the game, please refer to the project documentation or get in touch for assistance.

## Have Fun playing Rush Hour!

Project is under development 🛠
