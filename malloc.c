#include "malloc.h"
#include "heap.h"
#include <unistd.h>
#include <string.h>

#define MINIMUM_BLOCK_SIZE 4096 // Minimum block size requested via sbrk

// Global variables
free_mem_block_t free_memory_heap[MAX_HEAP_BLOCKS];
int current_heap_size = 0;

typedef struct memory_block {
    size_t size;
} memory_block_t;

// Custom malloc implementation
void *malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    size_t total_size = size + sizeof(memory_block_t);
    free_mem_block_t block = heap_extract_block(free_memory_heap, &current_heap_size, total_size);

    if (block.size != 0) {
        memory_block_t *header = (memory_block_t *)block.address;
        header->size = block.size;
        return (void *)(header + 1);
    }

    // Request new memory from the system
    size_t request_size = total_size < MINIMUM_BLOCK_SIZE ? MINIMUM_BLOCK_SIZE : total_size;
    memory_block_t *header = sbrk(request_size);
    if (header == (void *)-1) {
        return NULL;
    }

    header->size = request_size;
    return (void *)(header + 1);
}

// Custom free implementation
void free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    memory_block_t *header = (memory_block_t *)((char *)ptr - sizeof(memory_block_t));
    free_mem_block_t block = {header->size, (char *)header};

    heap_insert(free_memory_heap, &current_heap_size, block);
}

// Custom realloc implementation
void *realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return malloc(size);
    }

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    memory_block_t *header = (memory_block_t *)((char *)ptr - sizeof(memory_block_t));
    if (header->size >= size) {
        return ptr;
    }

    void *new_ptr = malloc(size);
    if (new_ptr != NULL) {
        memcpy(new_ptr, ptr, header->size - sizeof(memory_block_t));
        free(ptr);
    }
    return new_ptr;
}
