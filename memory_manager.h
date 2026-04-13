#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#define TOTAL_MEMORY 100

extern int used_memory;

int allocate_memory(int size);
void free_memory(int size);

#endif
