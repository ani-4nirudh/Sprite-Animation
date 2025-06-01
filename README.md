# Sprite Animation
This repository creates an animation of trees using a sprite sheet with help of SDL3 library.

## Instructions
```
# Create the following folders
mkdir -p build lib

# Clone the SDL3 library
cd lib
git clone https://github.com/libsdl-org/SDL.git vendored/SDL

# Clone the SDL3 Image library
git clone https://github.com/libsdl-org/SDL_image.git

# Generate build files
cd ../build
cmake -S ..
make -j${nproc}

# Run the project
./trees
```