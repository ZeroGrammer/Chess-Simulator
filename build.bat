
@echo off
setlocal

cd /D "%~dp0"

set SDL2_DIR=".\middleware\SDL2"

if not exist %SDL2_DIR% (
   echo SDL2 folder not found in the middleware directory!
   echo Run the install-dependencies.bat file to install SDL2
   exit /b
)

if not exist "bin" (
    mkdir bin
    xcopy /E /I ".\middleware\SDL2\SDL2-2.28.1\lib\x64\*.dll" ".\bin\"
    xcopy /E /I ".\middleware\SDL2\SDL2_image-2.6.3\lib\x64\*.dll" ".\bin\"
)

pushd bin

set FLAGS=/fsanitize=address /EHsc /MP /Zi /W4

set INCLUDE_PATH=/I"..\middleware\SDL2\SDL2-2.28.1\include"^
                 /I"..\middleware\SDL2\SDL2_image-2.6.3\include"

set LIB_PATH=/LIBPATH:"..\middleware\SDL2\SDL2-2.28.1\lib\x64"^
             /LIBPATH:"..\middleware\SDL2\SDL2_image-2.6.3\lib\x64"

set SYSTEM_LIBS=Shell32.lib kernel32.lib 

set SDL_LIBS=SDL2main.lib SDL2.lib SDL2_image.lib

set SOURCE_FILES=..\source\main.cpp ^
                 ..\source\game.cpp ^
                 ..\source\bot.cpp ^
                 ..\source\move_stack.cpp ^
                 ..\source\Chess\board.cpp ^
                 ..\source\Chess\move_engine.cpp ^
                 ..\source\Graphics\window.cpp ^
                 ..\source\Graphics\log.cpp ^
                 ..\source\Graphics\renderer.cpp

set OUTPUT_EXE=chess.exe

call cl %FLAGS% ^
        %INCLUDE_PATH% ^
        %SOURCE_FILES% ^
        %SYSTEM_LIBS% ^
        /link %LIB_PATH% %SDL_LIBS% ^
        /SUBSYSTEM:CONSOLE /OUT:%output_exe% 

popd
endlocal
