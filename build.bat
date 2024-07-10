
@echo off
setlocal

cd /D "%~dp0"

if not exist "bin" (
    mkdir bin
    xcopy /E /I ".\middleware\SDL2\lib\*.dll" ".\bin\"
)

pushd bin

set FLAGS=/EHsc /Zi /W4

set INCLUDE_PATH=/I"..\middleware\SDL2\include"
set LIB_PATH=/LIBPATH:"..\middleware\SDL2\lib"

set SYSTEM_LIBS=Shell32.lib kernel32.lib 
set SDL_LIBS=SDL2main.lib SDL2.lib SDL2_image.lib SDL2_ttf.lib

set SOURCE_FILES=..\source\main.cpp ^
                 ..\source\game.cpp ^
                 ..\source\Graphics\window.cpp ^
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
