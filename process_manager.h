//-------------------------------------------------------------------------------------
//------------------------------ PROCESS_MANAGER.H ------------------------------------
//-------------------------------------------------------------------------------------

#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

typedef struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int memory;
    int isolation_id;
    struct Process *next;   // <-- this is critical for linked list traversal
} Process;

Process* create_process(int pid, int burst_time, int memory, int isolation_id);
void add_process(Process **head, int pid, int burst_time, int memory, int isolation_id);
void print_processes(Process *head);
void schedule_round_robin(Process *head, int time_quantum);

#endif

