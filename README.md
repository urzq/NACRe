# NACRe
Not A Cube Renderer, a little forward rendering engine / game engine :)

![](https://github.com/urzq/NACRe/blob/master/screenshot.png)

Several basic functionalities that you can expect from a game engine are implemented, including: 
* context creation
* shader management
* texture management
* vertex buffer management
* input handler
* basic scene system

It also has CMake support, and several libraries are included as submodules (see .gitmodules).

# Instructions to build:
```bash
git clone --recursive https://github.com/urzq/NACRe
cd NACRe
mkdir build
cd build
cmake ..
```

# Controls 
Press ² to display ImGUI
Arrows + mouse control.