# Tetris
![main_game](https://github.com/alex-fok/tetris/blob/main/images/main_game.png?raw=true)
## Description

Cross-platform Tetris using [SFML Library](https://www.sfml-dev.org/).

## Installation

### Prerequisite Libraries
- [CMake](https://cmake.org/download/)
- For Linux users, a series of system packages will need to be installed. Here are the commands for Ubuntu OS:
  ```
  sudo apt update
  sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev
  ```
### Steps

<strong>Build</strong>

1. Create a `/build` folder in the repo
2. Navigate to `/build` run the following command to build the application.

   ```
   cmake ..
   ```
<strong>Run</strong>

1. Set environment variable `ENVIRONMENT=dev`.

    ```
    export ENVIRONMENT=dev
    ```
2. Run the executable `Tetris` in `/build/bin/Debug`.
