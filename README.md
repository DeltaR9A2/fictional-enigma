# Ninmu Nanmu: Love and Freedom

Information about this game can be found at http://ninmunanmu.com/

## Compiling

This game is being developed on a 64bit Arch Linux system where it is built using a combination of tools including sed, imagemagick, make, and gcc. Many of the build steps exist to simplify the development process, and might be eliminated in future versions as the game becomes more "complete".

Also, this git rpository does not contain any of the "binary resources" of the game, including all audio and graphics. These resources are not necessary to compile the game, but it will not run without them and the build system may report errors regarding the missing resources.

### Platform Support

It should be possible to compile this game on any platform supported by SDL2 (http://libsdl.org/) though I can only verify that it works on 64bit Linux systems. Building the game requires an up-to-date ANSI C compiler; Microsoft's Visual C compiler is NOT compliant with the current ANSI standard and will not work.