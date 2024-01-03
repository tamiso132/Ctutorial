
#include "alloc.h"

#define MAX_SIZE 4096
#define RESERVED_BYTES 32

typedef struct Node // 32 bytes are reserved
{
    uint16_t size;
    uint16_t prev_size;
    // here is the size
} Node;

static char *Memory[MAX_SIZE];
// 32 bytes are reserved

static uint32_t index = 0;
static uint32_t prev_val = 0;

void *allocate_memory(uint32_t size)
{
    Node *node = (Node *)&(Memory[index]);
    node->size = size;
    node->prev_size = prev_val;
    prev_val = size;

    index += size + RESERVED_BYTES;
    return (void *)&node[RESERVED_BYTES];
}

void free_memory(void *pointer)
{
}
