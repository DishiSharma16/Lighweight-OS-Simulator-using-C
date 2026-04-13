#include <stdio.h>        // for printf
#include <stddef.h>       // for NULL
#include "process_manager.h"
#include "memory_manager.h"

int main() {
    Process *head = NULL;   // linked list head

    // Correct usage: pass &head as the first argument
    add_process(&head, 1, 10, 50, 101);
    add_process(&head, 2, 5, 30, 102);
    add_process(&head, 3, 8, 40, 103);

    // Correct usage: pass head as argument
    print_processes(head);

    printf("\n=== Scheduling (Round Robin, quantum=3) ===\n");
    schedule_round_robin(head, 3);

     // At the end, show memory usage
    printf("\nFinal memory usage: %d/%d\n", used_memory, TOTAL_MEMORY);

    return 0;
}
