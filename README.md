
# Chess

**A WORK IN PROGRESS!**

a simple chess simulator built using the SDL2 graphics library

### Dependencies:

[SDL2](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.1) \
[SDL2_image](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3) \
[SDL2](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.1) 

(Target operating system: Windows)

### How to build the project

There is install-dependencies.bat script file in the repo that can be used to install SDL2, SDL2_image and SDL2_tff using curl. \
You can manually install all the dependencies from the links given above and place them in the middleware/SDL2 folder.

To compile this application make sure you have the Visual Stuio C++ compiler 
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