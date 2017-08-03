#ifndef JL_H
#define JL_H
typedef struct{
	unsigned char r,g,b,a;
}jl_Color;
const jl_Color
JL_BLACK={0,0,0},
JL_RED={255,0,0},
JL_GREEN={0,255,0},
JL_BLUE={0,0,255},
JL_WHITE={255,255,255};

extern char JL_SOFTWARE_REN;

void jl_init(void);
void jl_quit(char*);
void jl_frame(void);
void jl_clear(jl_Color);
void jl_square( float, float, float, jl_Color);

extern const unsigned long JL_RAND_MAX;
int JL_RAND(void);
#define jl_rand(lo,hi)\
	(lo + JL_RAND()/((JL_RAND_MAX+1)/(hi - lo)))
#endif
