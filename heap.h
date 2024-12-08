#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

#define MAX_HEAP_BLOCKS 1000 // Maximum number of blocks in the heap

typedef struct free_mem_block {
    size_t size;      // Size of the block
    char *address;    // Address of the block
} free_mem_block_t;

// Function prototypes for heap operations
void heap_insert(free_mem_block_t heap[], int *heap_size, free_mem_block_t block);
free_mem_block_t heap_extract_block(free_mem_block_t heap[], int *heap_size, size_t size);

#endif // HEAP_H
