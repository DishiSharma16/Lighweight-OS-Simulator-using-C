#include <stdio.h>
#include "memory_manager.h"

int used_memory = 0;

int allocate_memory(int size) {
    if (used_memory + size <= TOTAL_MEMORY) {
        used_memory += size;
        return 1; // success
    } else {
        printf("Not enough memory to allocate %d units\n", size);
        return 0; // fail
    }
}

void free_memory(int size) {
    used_memory -= size;
    if (used_memory < 0) used_memory = 0;
    printf("Freed %d units, used: %d/%d\n", size, used_memory, TOTAL_MEMORY);
}
