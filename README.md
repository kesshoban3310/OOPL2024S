# PTSD Template

This is a [PTSD](https://github.com/ntut-open-source-club/practical-tools-for-simple-design) framework template for students taking OOPL2024s.

## Quick Start

1. Use this template to create a new repository
   ![github screenshot](https://github.com/ntut-rick/ptsd-template/assets/126899559/ef62242f-03ed-481d-b858-12b730c09beb)

2. Clone your repository

   ```bash
   git clone YOUR_GIT_URL --recursive
   ```

3. Build your project

  > [!WARNING]
  > Please build your project in `Debug` because our `Release` path is broken D:
   
   ```sh
   cmake -DCMAKE_BUILD_TYPE=Debug -B build # -G Ninja
   ```
   better read [PTSD README](https://github.com/ntut-open-source-club/practical-tools-for-simple-design)

## PTSD 更改內容

### PTSD/include/config.hpp

```c++
constexpr unsigned int WINDOW_WIDTH = 16 * 16 * 3;
constexpr unsigned int WINDOW_HEIGHT = 14 * 16 * 3;
```

### PTSD/src/Core/Texture.cpp

```c++
GL_LINEAR -> GL_NEAREST
```
