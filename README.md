# 3D Rubik's Cube Engine

A C++ based 3D Rubik's Cube simulation built from scratch. 
It uses its own 3d rendering pipline(camera basis, coordinate transformations) and sdl2 for low-level drawing.

## Dependencies

* **C++ Compiler:** Must support C++17 (e.g., GCC, Clang).
* **SDL2 Library:** Simple DirectMedia Layer for creating the window and drawing pixels.
* **Make:** For building the project.

##  Build Instructions

1.  **Compile the project:**
    ```bash
    make rubix
    ```

2.  **Run the executable:**
    ```bash
    ./rubix
    ```

3.  Delete the executables:
    ```bash
    make clean
    ```

##  Controls

### Cube Manipulation

It follows standard cubing notations:

| Key | Face | Action |
| :--- | :--- | :--- |
| **f** | Front | Rotate Front Face Clockwise|
| **b** | Back | Rotate Back Face Clockwise|
| **u** | Up | Rotate Top Face Clockwise|
| **d** | Down | Rotate Bottom Face Clockwise|
| **l** | Left | Rotate Left Face Clockwise|
| **r** | Right | Rotate Right Face Clockwise|
| **F** | Front | Rotate Front Face Anticlockwise|
| **B** | Back | Rotate Back Face Anticlockwise|
| **U** | Up | Rotate Top Face Anticlockwise|
| **D** | Down | Rotate Bottom Face Anticlockwise|
| **L** | Left | Rotate Left Face Anticlockwise|
| **R** | Right | Rotate Right Face Anticlockwise|
| **s** | Scramble | Scramble the cube (25 moves) |
| **o** | Reset | Reset/Solve the cube |

### Camera Controls

| Key | Action |
| :--- | :--- |
| **Arrow Up/Down** | Rotate Camera Vertically ($\phi$) |
| **Arrow Left/Right** | Rotate Camera Horizontally ($\theta$) |
| **- / + (Minus/Equals)**| Zoom In/Out ($\rho$) |
| **q** | Quit Application |


### The Rendering Pipeline

Unlike standard engines, I calculated the pixel coordinates for the cube vertices manually.
- The cube stores an vector of size 54 with the colors for each cell.
- It also stores a vector of 54 facelets defined in 3D $(x, y, z)$ space. 
- Each facelet stores the position and normal vector for a cell.
- The camera has a 3 basis vectors - forward, right, up.
- Dot product of the basis vectors with the normal vectors of each facelet deciding which facelets to render.

##  File Structure

* `main.cpp`       : SDL event loop and input processing.
* `cube.cpp/h`     : cube state, facelet generation, and rotation logic.
* `camera.cpp/h`   : spherical coordinates for the camera and basis vector calculations.
* `geometry.cpp/h` : helpers for math operations (dot products, vector rotations).
* `constants.h`    : stores screen dimensions, colors, etc.
