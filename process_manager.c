#include <stdio.h>
#include <stdlib.h>
#include "process_manager.h"
#include "memory_manager.h"

// Create a new process node
Process* create_process(int pid, int burst_time, int memory, int isolation_id) {
    Process *new_process = (Process*)malloc(sizeof(Process));
    new_process->pid = pid;
    new_process->burst_time = burst_time;
    new_process->remaining_time = burst_time;
    new_process->memory = memory;
    new_process->isolation_id = isolation_id;
    new_process->next = NULL;
    return new_process;
}

// Add a process to the linked list, with memory allocation check
void add_process(Process **head, int pid, int burst_time, int memory, int isolation_id) {
    if (!allocate_memory(memory)) {
        printf("Process %d could not be created due to insufficient memory.\n", pid);
        return;
    }

    Process *new_process = create_process(pid, burst_time, memory, isolation_id);
    if (*head == NULL) {
        *head = new_process;
    } else {
        Process *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_process;
    }
}

// Print all processes in the list
void print_processes(Process *head) {
    printf("=== Process List ===\n");
    Process *temp = head;
    while (temp != NULL) {
        printf("PID: %d | Burst: %d | Memory: %d | IsolationID: %d\n",
               temp->pid, temp->burst_time, temp->memory, temp->isolation_id);
        temp = temp->next;
    }
}

// Round Robin scheduler
void schedule_round_robin(Process *head, int time_quantum) {
    Process *current = head;
    while (current != NULL) {
        if (current->remaining_time > 0) {
            int run_time = (current->remaining_time > time_quantum) ? time_quantum : current->remaining_time;
            current->remaining_time -= run_time;
            printf("Running PID %d for %d units, remaining: %d\n",
                   current->pid, run_time, current->remaining_time);

            // Free memory when process finishes
            if (current->remaining_time == 0) {
                free_memory(current->memory);
                printf("Process %d finished, freed %d units. Used: %d/%d\n",
                       current->pid, current->memory, used_memory, TOTAL_MEMORY);
            }
        }

        current = current->next;
        if (current == NULL) current = head; // loop back to start

        // stop when all processes are finished
        int all_done = 1;
        Process *check = head;
        while (check != NULL) {
            if (check->remaining_time > 0) { all_done = 0; break; }
            check = check->next;
        }
        if (all_done) break;
    }
}
