# Intro

I created this little game in my second year studying CS, as a passion project in order to learn C and game development.  
Came back to it after two years and I'm thinking about expanding it into a bigger game.

# How to play it for yourself

SDL: I do not include any SDL source code inside my project, so you will need to follow these steps in order to install SDL and SDL_image (Works on Linux and macOS, have not tested it on Windows):

```bash
git clone https://github.com/libsdl-org/SDL
git clone https://github.com/libsdl-org/SDL_image

# Assuming you cloned both repoitories in the same location
cmake -S ./SDL -B ./SDL/build
cmake --build ./SDL/build
cmake --install ./SDL/build

cmake -S ./SDL_image -B ./SDL_image/build
cmake --build ./SDL_image/build
cmake --install ./SDL_image/build
```
After that you will need to compile the game by running:

```bash
cmake -S . -B build
cmake --build build
./build/shooter
```
