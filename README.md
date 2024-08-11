
# Chess

**A WORK IN PROGRESS!**

a simple chess simulator built using the SDL2 graphics library

### Dependencies:

[SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.1) \
[SDL2_image](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3) \

(Target operating system: Windows x64)

### How to build the project

There is install-dependencies.bat script file in the repo that can be used to install SDL2 and SDL2_image using curl.

```console
$ .\install-dependencies.bat
```

You can manually install all the dependencies from the links given above and place them in the middleware/SDL2 folder.

To compile this application make sure you have the Visual Stuio C++ compiler \
installed, and your running a terminal instance that recognises cl.exe

To compile the program call the build.bat script from the main directory:
```console
$ .\build.bat
```

### How to run the program

make sure your calling the executale from the main project directory

To run this application:
```console
$ .\bin\chess.exe
```

### Keybinds for the application

general settings
 - x -> reset position on the board
 - f -> flip the board

hold down any of the following key to promote to a different minor piece
- 1 -> promote to a Queen
- 2 -> promote to a Rook
- 3 -> promote to a Bishop
- 4 -> promote to a Knight

history of the game
- Left-Arrow -> to look into the hisory of the game
- Right-Arrow -> to go to the latest position 

Note: When you are looking into the history of the game you cannot move the pieces (since branching is not handled yet).
      Just press Right-Arrow to go to the latest move and the continue the game.

### NOTE
You can compile it for 32-bit, you will just have to change the path for SDL2 libs folders to point at 32-bit binaries in build.bat.
where ever you see x64 just replace it with x86 and it should compile to x86 (Given you are using cl.exe in a x86 environment)
