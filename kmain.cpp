#include <stdint.h>

#include "include/asm.h"
#include "winsis/vgasrc.cpp"
#include <cstdio>
#include <cstdlib>

extern "C" void kmain(int framebuffer, int bpp)
{
    // Deprecated command line mode	
}
extern "C" void wmain(int32_t framebuffer, int bpp)
{
	vgakurulum(framebuffer);

	while(0){}
}





 

