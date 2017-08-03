# JL
Create cross platform graphics and sound and eliminate common boilerplate code that using libraries like SDL2 entails. This library statically depends on different lirbaries, depending on the platform deployed to. Static dependencies are chosen to make the applications easily deployable to other machines.
For Windows, Mac OSX, and *nix, iOS, and Android, SDL2 is a dependency.
For the web with emscripten, emscripten and SDL2 are dependencies.

# How the coordinate system works:

To handle various aspect ratios, the coordinate system takes place in the largest square that can fit inside a rectangular screen. Therefore, an x/y position is represented by a floating point number, where a number between 0 and 1 will place anywhere inside the edge of this aspect square.
When a window is resized, all coordinates are automatically readjusted to be handled.

# Stucture Types:
jl_Color - A color contains rgba information for rendering.
Color Constants: JL_BLACK, JL_RED, JL_GREEN, JL_BLUE, JL_WHITE

# Global Flags:
JL_SOFTWARE_REN - After calling JL_Init, if a hardware-accelerated graphics context could not be created, then a software rendering fallback will be used instead. JL_SOFTWARE_REN is set to 1 when a software rendering context is created. Use this flag to make the optimizations necessary to handle the lower performance.

# void jl_init(void):
Call this function once to setup the entire graphics context, the audio context, and all other apsects of the library such as random number generation. On desktops, a graphics context is represented by a fullscreen, resizable window. On mobile, it is represented by a fullscreen app that is not resizable or rotatable. In emscripten for the web, the context will fill the size of its container, for instance a div. When the window is closed, jl_quit is also automatically called, and the library will clean up all resources allocated automatically.

# void jl_quit(char*):
jl_quit is automatically called when the window is closed by pressing "x". So you may not even need to call this function manually at all. If you would like to abort the program in the event of some error, jl_quit supports passing a string error message. The error message will be printed on the standard error. If an error message is passed, the exit code returned by the program is 1, otherwise the exit code is 0.

# void jl_frame(void):
jl_frame steps the context along by a single frame. Use this function at the beginning of a loop to display, and on the subsequent iteration of the loop, input will be collected. This function allows a program structure to take any form the user desires. The typical structure for a video game, for instance, is a main loop. However, jl_frame can be called from anywhere, and therefore allows for several game loops and nested loops as well.

# void jl_clear(jl_Color):
jl_clear will clear the screen to a solid color. Pass the rgba value to clear to. If the color is transparent, then the previous contents will still be visible behind the clear.

# void jl_square( float x, float y, float dim, jl_Color col):
jl_square draws a square at location x, y, with a length of size dim, and is rendered using the color col. A square is drawn centered from the x/y position rather than from the upper-left.

# jl_rand(lo,hi)
jl_rand is a macro that supports random number generation for both floats and integer types. The random value will contain any possible number between lo and hi.

# Coming Soon
Abstractions over common texture-loading operations.
Abstractions over sound-loading and sound-playing operations.
OpenGL context creation support with a single function call.
Abstractions over network.
An interface for the go programming language.
An interface for the C++ programming language with destructors.
