#include "libBareMetal.h"
#include <stdint.h>

#define __PRINTF_H_IMPLEMENTATION__
#include "utils/printf.h"
#include "utils/math.h"
#define __STACK_ALLOC_IMPLEMENTATION__
#include "utils/stack_allocator.h"

void putpixel(int x, int y, char red, char green, char blue);
#define UR_SCREEN_WIDTH *(uint16_t *)(0x5088)
#define UR_SCREEN_HEIGHT *(uint16_t *)(0x508A)
#define UR_PUT_PIXEL putpixel
#define UR_MALLOC stackAllocatorStaticMalloc

#define UR_REALLOC stackAllocatorStaticRealloc

#define UR_FREE stackAllocatorStaticFree

#include "utils/universal_renderer.h"


unsigned char *frame_buffer;
uint16_t x_res, y_res;
uint8_t depth;

int main(void)
{
	// Gather video memory address, x & y resolution, and BPP
	frame_buffer = (unsigned char *)(*(uint64_t *)(0x5080));
	x_res = *(uint16_t *)(0x5088);
	y_res = *(uint16_t *)(0x508A);
	depth = 32;
	// urClearScreen(UR_BLACK);
	printf("\n Hello World!! %d/n", 10);
	//urDrawCircle((URPointI){.x = x_res/2, .y = y_res / 2}, 100, UR_RED);
}

void putpixel(int x, int y, char red, char green, char blue)
{
	int offset = ((y * x_res) + x) * (depth / 8);
	frame_buffer[offset+0] = blue;
	frame_buffer[offset+1] = green;
	frame_buffer[offset+2] = red;
}