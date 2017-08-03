# jl
A quick way to create cross-platform graphics and sound and eliminates boilerplate code.

How the coordinate system works:

To handle various aspect ratios, the coordinate system takes place in the largest square that can fit inside a rectangular screen. Therefore, an x/y position is represented by a floating point number, where a number between 0 and 1 will place anywhere inside the edge of this aspect square.
When a window is resized, all coordinates are automatically readjusted to be handled.

Stucture Types:
jl_Color - A color contains rgba information for rendering.
Color Constants: JL_BLACK, JL_RED, JL_GREEN, JL_BLUE, JL_WHITE

GLobal Flags:
JL_SOFTWARE_REN - After calling JL_Init, if a hardware-accelerated graphics context could not be created, then a software rendering fallback will be used instead. JL_SOFTWARE_REN is set to 1 when a software rendering context is created. Use this flag to make the optimizations necessary to handle the lower performance.

void jl_init(void):
Call this function once to setup the entire graphics context, the audio context, and all other apsects of the library such as random number generation. On desktops, a graphics context is represented by a fullscreen, resizable window. On mobile, it is represented by a fullscreen app that is not resizable or rotatable. In emscripten for the web, the context will fill the size of its container, for instance a div. When the window is closed, jl_quit is also automatically called, and the library will clean up all resources allocated automatically.

void jl_quit(char*):
As stated before, jl_quit is automatically called when the window is closed by pressing "x". So only use this function to exit the window in the event of an error. For handling errors, jl_quit supports passing a string error message. The error message will be printed on the standard error.

void jl_frame(void):
void jl_clear(jl_Color):
void jl_square( float x, float y, float dim, jl_Color):

extern const unsigned long JL_RAND_MAX;
int JL_RAND(void);
#define jl_rand(lo,hi)\
(lo + JL_RAND()/((JL_RAND_MAX+1)/(hi - lo)))
