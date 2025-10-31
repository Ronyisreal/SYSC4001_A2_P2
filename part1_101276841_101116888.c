/*
 * SYSC4001 Assignment 2 - Part II - Question 1
 * Students: 101276841, 101116888
 * 
 * Basic fork demonstration with two concurrent processes
 * Each process runs indefinitely with its own counter
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int counter = 0;
    pid_t pid;
    
    printf("Starting program. Parent PID: %d\n", getpid());
    
    // Create child process
    pid = fork();
    
    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child Process (Process 2)
        printf("Child Process started. PID: %d\n", getpid());
        
        while (1) {
            printf("Process 2 (Child) - Counter: %d\n", counter);
            counter++;
            sleep(1);  // Delay to slow display speed
        }
    }
    else {
        // Parent Process (Process 1)
        printf("Parent Process continuing. PID: %d, Child PID: %d\n", 
               getpid(), pid);
        
        while (1) {
            printf("Process 1 (Parent) - Counter: %d\n", counter);
            counter++;
            sleep(1);  // Delay to slow display speed
        }
    }
    
    return 0;
}

/*
 * To compile: gcc -o part1 part1_101276841_101116888.c
 * To run: ./part1
 * 
 * To stop:
 * 1. Open another terminal
 * 2. Find PIDs: ps aux | grep part1
 * 3. Kill both: kill <parent_pid> <child_pid>
 *    or: killall part1
 */
