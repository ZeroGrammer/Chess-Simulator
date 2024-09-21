@echo off
setlocal

cd /D "%~dp0"

set SDL2_DIR="middleware/SDL2"

set SDL2_URL="https://github.com/libsdl-org/SDL/releases/download/release-2.28.1/SDL2-devel-2.28.1-VC.zip"
set SDL2_IMG_URL="https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-VC.zip"
set SDL2_TTF_URL="https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-VC.zip"

if not exist %SDL2_DIR% (

   mkdir %SDL2_DIR% 

   pushd %SDL2_DIR%

   echo Installing SDL2 from %SDL2_URL%
   curl -L -o SDL2.zip %SDL2_URL%
   echo Done Installing SDL2!

   echo Installing SDL2_image from %SDL2_IMG_URL%
   curl -L -o SDL2_IMG.zip %SDL2_IMG_URL%
   echo Done Installing SDL2_image!

   echo Installing SDL2_ttf from %SDL2_TTF_URL%
   curl -L -o SDL2_TTF.zip %SDL2_TTF_URL%
   echo Done Installing SDL2_image!

   echo extracting files...
   tar -xf SDL2.zip
   tar -xf SDL2_IMG.zip
   tar -xf SDL2_TTF.zip
   echo Done Extracting files!

   del SDL2.zip
   del SDL2_IMG.zip
   del SDL2_TTF.zip

   popd

   echo Now you can run the build.bat file to compile the program!
)
