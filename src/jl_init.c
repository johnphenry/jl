#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jl.h"
#include "jl_private.h"


char JL_SOFTWARE_REN;

const unsigned long JL_RAND_MAX = RAND_MAX;

SDL_Renderer*ren;
static int winDim;
static int xOffset;
static int yOffset;
static SDL_Window*win;

static void UPDATE_WIN_SIZ(void){
	int w,h;
	SDL_GetWindowSize(win,&w,&h);
	int min = (w<h)?w:h;
	winDim = min;
	#define ACTION(a,b) a = (((w>h)?w:h) - min )/2;b=0;
	if(w>h){
		ACTION(xOffset,yOffset);
	}else{
		ACTION(yOffset,xOffset);
	}
}
void jl_quit(char*error){
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	if(error) puts(error);
	exit( error == NULL );
}
void jl_init(void){
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	{
		Uint32 window_type = SDL_WINDOW_RESIZABLE;
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		#define POS SDL_WINDOWPOS_UNDEFINED
		win=SDL_CreateWindow("",POS,POS,dm.w,dm.h,window_type);
		if(!win) jl_quit("Window creation failed.");
		UPDATE_WIN_SIZ();
	}
	{
		#define RCREATE(type) ren=SDL_CreateRenderer(win,-1,type)
		RCREATE(SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
		|SDL_RENDERER_TARGETTEXTURE);
		if(!ren){
			RCREATE(SDL_RENDERER_SOFTWARE
			|SDL_RENDERER_TARGETTEXTURE);
			JL_SOFTWARE_REN = 1;
		}
		if(!ren) jl_quit("Renderer creation failed!");
	}
}

void jl_frame(void){
	SDL_RenderPresent(ren);
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				jl_quit(NULL);
			break;
			case SDL_WINDOWEVENT:
				switch(e.window.event){
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						UPDATE_WIN_SIZ();
					break;
				}
			break;
			case SDL_KEYDOWN:
			break;
			case SDL_KEYUP:
			break;
				
		}
	}
}
static void SET_COLOR(jl_Color c){
	SDL_SetRenderDrawColor(ren,c.r,c.g,c.b,c.a);
}
void jl_clear(jl_Color c){
	SET_COLOR(c);
	SDL_RenderClear(ren);
}
void jl_square( float x, float y, float dim, jl_Color c ){
	SET_COLOR(c);
	int d = dim *winDim;
	SDL_Rect r={ x*winDim+xOffset, y*winDim+yOffset, d, d};
	SDL_RenderFillRect(ren,&r);
}

#include <string.h>
#include <SDL2/SDL2_gfxPrimitives.h>
void jl_string( char*str, float x, float y, float w, float h, jl_Color c ){
	#define TEXT_SIZ 8
	unsigned BUF_WIDTH = TEXT_SIZ * strlen(str);
	SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, BUF_WIDTH, TEXT_SIZ);
	SDL_SetRenderTarget( ren, tex );
	jl_clear(JL_BLACK); /* I am thinking, why not just make bg transparent? If I implement a buffer type, this will be easy.*/
	stringRGBA(ren, 0, 0, str, c.r, c.g, c.b, 255 );
	SDL_SetRenderTarget( ren, NULL );
	SDL_Rect r={ x*winDim+xOffset, y*winDim+yOffset, w*winDim, h*winDim };
	SDL_RenderCopy( ren, tex, NULL, &r );
	SDL_DestroyTexture(tex);
}
/*TOADD:

A timer. I definately need software timers to use.
These timers can be checked against and can cause things to happen.
Of the form:

Finally, I think this project as a whole needs to be re-thought and redone.

It needs to:
1. Be designed for emscripten support.
2. Use source control
3. Link to all of its dependencies statically.
4. Be able to be easily installed on the system as a static library.

jl_Timer fall_time = interval( JL_SECOND );
then later:
if( fall_time ){
	block_fall, ect.
}



Modify the string function so that the string "nicely fits" inside the rectangle.
The text will basically scale as time goes on.

However, when it comes to something like draw_int, which will primarily be used for scores,
I believe that one should always assume a certain number of characters, namely the
max number of characters required to rendr an unsigned int string.

It would also be nice if I could tile up the screen and have my strings drawn in a set of tiles.

Other tricks would be: outlining text. If I were to render two texts of differnet colors, I could outline it.

jl_int_string
Add a better way for graphics to scale into the central square through code reuse.
I'm thinking that a JL_rect could potentially contain a texture, but if the pointer
is set to NULL then a solid color is simply drawn. This ultimately means less functions.

I need a way to describe algorithms such that they can continue to display in all the
out-of-bounds areas. There needs to be some indicator of: beginning of screen, ect.

Otherwise, how can I take full advantage of tile space in a platform game?

I can also build libraries on top of this one.

But even like, let's say I was making that sine demo. I'd want to take full advantage
of the potential screen space but still guarantee that the small square will contain every letter.

For instance I can easily build a platformer engine on top of this that I can then use for
multiple games.

Finally, I want to make a build tool. Something that will package a game for me correctly depending on
the platform.
Makes a mac application bundle, ect.
*/
int JL_RAND(void){
	return rand();
}

#include <math.h>
int main(){
	jl_init();
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	SDL_Texture *t = SDL_CreateTexture(ren,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 64);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor( ren, 0, 0, 0, 128 );
	SDL_SetRenderTarget(ren, t);
	SDL_RenderClear(ren);
	SDL_SetRenderTarget(ren,NULL);
	for(;;){
		jl_clear(JL_WHITE);
		SDL_Rect r = { 0, 0, 64, 64 };
		SDL_RenderCopy(ren,t, NULL, &r);
		jl_frame();
	}
}
