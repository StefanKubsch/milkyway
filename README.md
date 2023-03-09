# milkyway

This is my approach on a minimal 1K/2K/4K demoscene framework for use with GLSL shaders.

Environment: C++ x86, Visual Studio 2022, crinkler used as linker substitute, targeted at Windows 10/11.

The framework is "stripped" to the max, only code that is REALLY neccessary for running is included.

Core of this framework and the key to low binary sizes is the implementation of a "custom entrypoint" (instead of the standard "main") and establishing a minimal prologue.

By doing this, CRT (C Runtime) is not used, so there is no linking against static or dynamic libraries. Once compiled and linked, you get a "freestanding" or "bare metal" application that is capable to run on a basic Windows machine.
Only OpenGL drivers are needed, everything else is working with Windows APIs.

On the other side, you´re not able to use C-functions like memset/memcpy or printf etc out of box. All stuff needs to be implemented by yourself.

Since we need some inline assembler, this is an x86/Win32 application.

What can this framework do for you?

1) Create a fullscreen window and an OpenGL context
2) Load all needed (and ONLY NEEDED!) OpenGL WGL extensions
3) Load and compile GLSL shader code
4) 4klang synthesizer integrated, load & play songs (https://github.com/hzdgopher/4klang)
5) Implement some basic and often needed functions without the use of a standard library (right now: memset, memcpy)
6) Run everything together!

Try it out!

This repo contains a "milkyway.exe" file under "Release", less than 3kB (2.44kB or 2507 Bytes to be exact) in size. It will run on any Windows 10 or 11 machine with a proper graphics adapter and OpenGL drivers.

The original filesize is around 6kB, but due to the use of "crinkler" (https://github.com/runestubbe/Crinkler) we can reduce the size.

crinkler settings are defined in Project/Linker/Additional Options:
/CRINKLER /RANGE:opengl32 /UNSAFEIMPORT /UNALIGNCODE

Further plans:

- implement a tool for compressing shader code like Shader_Minifier (https://github.com/laurentlb/shader_minifier)
- more work on code size (there are still some bytes buried, I think)

Feel free to use the code!

Why the name "milkyway"? In the 1990s, there was a german TV commercial for a candy bar called "MilkyWay. The tagline was "Der ist so leicht, der schwimmt sogar in Milch". Translated to english it is "It's so light, it even floats in milk". I find the name quite appropriate for a very minimal framework.
