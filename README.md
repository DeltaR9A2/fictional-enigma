# Ninmu Nanmu: Love and Freedom

NNLAF is a game combining elements of 2D platformers, visual novels, and JRPGs. It is developed by John Colburn, with some assistance from Cameron McLagan and Jeremy Smith. It was originally funded by generous IndieGoGo contributors and has been in development since May 1st, 2013. There is no estimated release date, but development continues to crawl toward completion.

## Compiling

This game is being developed on a 64bit Arch Linux system using the traditional GNU toolchain (make, gcc, sed, etc). The makefiles also use imagemagick and ffmpeg to convert some of the game's graphics and audio during the build process.

The windows version is cross-compiled from linux using the mingw version of GCC.

Known Dependencies:
* LUA - http://lua.org/
* SDL2 - http://libsdl.org/
  * SDL2_image - http://www.libsdl.org/projects/SDL_image/
  * SDL2_mixer - http://www.libsdl.org/projects/SDL_mixer/
  * SDL2_gfx - http://cms.ferzkopp.net/index.php/software/13-sdl-gfx
* ImageMagick - http://www.imagemagick.org/
* ffmpeg - https://www.ffmpeg.org/

Note that ImageMagick and ffmpeg are not used after the build process; they are required to create game resources but are not required to run the game.
