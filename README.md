# Pong in "3D"

![gif](https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExOXZidnA5YXM3ODJ0cW1iajc1ZzZ4aWk3OG1wNzJkanFrdTFtYmVtMSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/os2cCCPk7hme3iSUSm/giphy.gif)

Pong game with a little bit of 3D graphics, written in OpenGL. \
Finished for now.

#### Featuring
- Pretty janky collisions
- Even worse score display
- Absolutely no colors

## Gameplay
Press W/S to control the player rectangle. \
Press Enter to switch between an AI and controling the opponent rectangle. \
Press Up/Down to control the opponent rectangle.

## Compilation

Clone the repo
```bash
git clone https://github.com/szulf/pong-3d && cd pong-3d
```

Build with cmake
```bash
mkdir build && cd build
cmake build ../
```

Compile the project
```bash
make
```

And run
```bash
./pong
```

---

Importing with Visual Studio almost works, you just need to change the path to the shaders in Game.cpp(because the directory structure differs there) from `../src/shader_name` to `../../../src/shader_name`(line 201).
