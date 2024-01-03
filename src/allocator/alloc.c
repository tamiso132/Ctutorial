#include <stdint.h>

#define MAX_ALLOCATION 1024

static unsigned int FIXED_BLOCK;

const char BUFFER[MAX_ALLOCATION];

void *custom_malloc(uint32_t blocks)
{
}