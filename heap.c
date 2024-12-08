#include "heap.h"
#include <stdio.h>
#include <math.h>

// Parent, left, and right child indices
unsigned int heap_parent(unsigned int index) {
    return (index - 1) / 2;
}

unsigned int heap_left_child(unsigned int index) {
    return (index * 2) + 1;
}

unsigned int heap_right_child(unsigned int index) {
    return (index * 2) + 2;
}

// Swap two heap blocks
void heap_swap(free_mem_block_t heap[], int index1, int index2) {
    free_mem_block_t temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

// Bubble up the block at a given index
void heap_bubble_up(free_mem_block_t heap[], int index) {
    int current = index;
    while (current > 0) {
        int parent = heap_parent(current);

        if (heap[current].size >= heap[parent].size) {
            break;
        }

        heap_swap(heap, current, parent);
        current = parent;
    }
}

// Bubble down the block at a given index
void heap_bubble_down(free_mem_block_t heap[], int heap_size, int current) {
    while (heap_left_child(current) < heap_size) {
        int left_child = heap_left_child(current);
        int right_child = heap_right_child(current);
        int smallest = left_child;

        if (right_child < heap_size && heap[right_child].size < heap[smallest].size) {
            smallest = right_child;
        }

        if (heap[current].size <= heap[smallest].size) {
            break;
        }

        heap_swap(heap, current, smallest);
        current = smallest;
    }
}

// Insert a block into the heap
void heap_insert(free_mem_block_t heap[], int *heap_size, free_mem_block_t block) {
    if (*heap_size >= MAX_HEAP_BLOCKS) {
        fprintf(stderr, "Heap is full\n");
        return;
    }

    heap[*heap_size] = block;
    heap_bubble_up(heap, *heap_size);
    (*heap_size)++;
}

// Extract a block that matches or exceeds the requested size
free_mem_block_t heap_extract_block(free_mem_block_t heap[], int *heap_size, size_t size) {
    for (int i = 0; i < *heap_size; i++) {
        if (heap[i].size >= size) {
            free_mem_block_t block = heap[i];
            (*heap_size)--;
            heap[i] = heap[*heap_size];
            heap_bubble_down(heap, *heap_size, i);
            return block;
        }
    }

    return (free_mem_block_t){0, NULL};
}
