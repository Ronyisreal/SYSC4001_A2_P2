# SYSC4001 Assignment 2 - Part II: Concurrent Processes in Unix

**Course:** SYSC4001 - Operating Systems  
**Assignment:** Assignment 2, Part II  
**Students:**
- Student 1: 101276841
- Student 2: 101116888

---

## Description

This repository contains implementations of concurrent process management in C/C++ under Linux, demonstrating the use of:
- `fork()` system call for process creation
- `exec()` system call family for program execution
- `wait()` system call for process synchronization
- Shared memory (`shmget`, `shmat`, `shmdt`, `shmctl`)
- Semaphores (`semget`, `semop`, `semctl`) for mutual exclusion

---

## Repository Structure
```
SYSC4001_A2_P2/
├── README.md                                    (This file)
├── explanation_fork_101276841_101116888.md      (Explanation of fork system call)
├── Makefile_101276841_101116888                 (Build automation)
│
├── part1_101276841_101116888.c                  (Question 1: Basic fork)
│
├── part2_101276841_101116888.c                  (Question 2: Parent process)
├── part2_child_101276841_101116888.c            (Question 2: Child executable)
│
├── part3_101276841_101116888.c                  (Question 3: Using wait)
│
├── part4_101276841_101116888.c                  (Question 4: Parent with shared memory)
├── part4_child_101276841_101116888.c            (Question 4: Child with shared memory)
│
├── part5_101276841_101116888.c                  (Question 5: Parent with semaphores)
└── part5_child_101276841_101116888.c            (Question 5: Child with semaphores)
```

---

## Requirements

- **Operating System:** Linux (tested on Ubuntu/Debian-based distributions)
- **Compiler:** GCC (GNU Compiler Collection)
- **Libraries:** Standard C library, POSIX IPC

---

## Compilation

### Using Makefile (Recommended)
```bash
# Compile all programs
make -f Makefile_101276841_101116888 all

# Compile individual parts
make -f Makefile_101276841_101116888 part1
make -f Makefile_101276841_101116888 part2
make -f Makefile_101276841_101116888 part3
make -f Makefile_101276841_101116888 part4
make -f Makefile_101276841_101116888 part5

# Clean compiled files
make -f Makefile_101276841_101116888 clean
```

### Manual Compilation
```bash
# Part 1
gcc -Wall -g -o part1 part1_101276841_101116888.c

# Part 2
gcc -Wall -g -o part2 part2_101276841_101116888.c
gcc -Wall -g -o part2_child part2_child_101276841_101116888.c

# Part 3
gcc -Wall -g -o part3 part3_101276841_101116888.c

# Part 4
gcc -Wall -g -o part4 part4_101276841_101116888.c
gcc -Wall -g -o part4_child part4_child_101276841_101116888.c

# Part 5
gcc -Wall -g -o part5 part5_101276841_101116888.c
gcc -Wall -g -o part5_child part5_child_101276841_101116888.c
```

---

## Execution

### Part 1: Basic Fork with Independent Counters

**Description:** Creates two processes, each with independent counters incrementing in infinite loops.
```bash
./part1
```

**To Stop:**
```bash
# In another terminal
ps aux | grep part1
kill  
# OR
killall part1
```

---

### Part 2: Fork with Exec and Multiples of 3

**Description:** 
- Process 1 (parent) increments counter and displays multiples of 3
- Process 2 (child) uses `exec()` to run separate program, decrements counter
```bash
./part2
```

**Expected Output:**
```
Cycle number: 0 - 0 is a multiple of 3
Cycle number: 1
Cycle number: 2
Cycle number: 3 - 3 is a multiple of 3
...
```

**To Stop:** `ps aux | grep part2` then `kill <pid>`

---

### Part 3: Using Wait System Call

**Description:**
- Process 1 increments until counter reaches 100, then waits for Process 2
- Process 2 decrements until counter reaches -500, then terminates
- Process 1 ends after Process 2 completes
```bash
./part3
```

**Note:** This program terminates automatically when Process 2 reaches -500.

---

### Part 4: Shared Memory Between Processes

**Description:**
- Two shared variables: `shared_multiple` (default 3) and `shared_counter`
- Process 1 increments `shared_counter` starting from 0
- Process 2 starts only when `shared_counter > 100`
- Both processes display multiples of `shared_multiple`
- Both terminate when `shared_counter > 500`
```bash
./part4
```

**Note:** Program terminates automatically when counter exceeds 500.

---

### Part 5: Semaphore Protection for Shared Memory

**Description:**
- Same as Part 4 but with semaphore protection
- Prevents race conditions when accessing shared variables
- Demonstrates mutual exclusion using POSIX semaphores
```bash
./part5
```

**Note:** Program terminates automatically when counter exceeds 500.

---

## Key Concepts Demonstrated

### 1. Process Creation (`fork`)
- Creating child processes
- Understanding return values
- Managing process hierarchy

### 2. Process Replacement (`exec`)
- Loading and executing different programs
- Replacing process image

### 3. Process Synchronization (`wait`)
- Parent waiting for child termination
- Preventing zombie processes
- Retrieving exit status

### 4. Inter-Process Communication (Shared Memory)
- Creating shared memory segments
- Attaching/detaching shared memory
- Reading/writing shared data

### 5. Process Synchronization (Semaphores)
- Creating and initializing semaphores
- Implementing mutual exclusion (mutex)
- P (wait) and V (signal) operations
- Preventing race conditions

---

## Troubleshooting

### Issue: "Exec format error"
**Solution:** Ensure child executables are compiled before running parent:
```bash
gcc -o part2_child part2_child_101276841_101116888.c
gcc -o part2 part2_101276841_101116888.c
./part2
```

### Issue: Shared memory segments persist after program crashes
**Solution:** Clean up manually:
```bash
# List shared memory
ipcs -m

# Remove specific segment
ipcrm -m 

# Remove all shared memory segments created by you
ipcs -m | grep $USER | awk '{print $2}' | xargs -I {} ipcrm -m {}
```

### Issue: Semaphores persist after program crashes
**Solution:**
```bash
# List semaphores
ipcs -s

# Remove specific semaphore
ipcrm -s 
```

### Issue: Process continues running after terminal closes
**Solution:**
```bash
ps aux | grep part[1-5]
kill -9 
```

---

## Testing

### Verify Fork Behavior
```bash
./part1 &
ps -ef | grep part1
# Should see two processes with different PIDs
```

### Verify Shared Memory
```bash
./part4 &
ipcs -m
# Should see shared memory segments
```

### Verify Semaphores
```bash
./part5 &
ipcs -s
# Should see semaphore
```

---

## Notes

- All programs use `sleep()` or `usleep()` to slow down display speed for readability
- Parts 1 and 2 run infinitely and must be manually terminated
- Parts 3, 4, and 5 terminate automatically when conditions are met
- Shared memory and semaphore keys are hardcoded (see source files)
- Error handling is included for all system calls

---

## References

- Linux Programming Interface by Michael Kerrisk (Chapter 24, 48, 53)
- Advanced Programming in the UNIX Environment by Stevens & Rago
- Linux man pages: `man 2 fork`, `man 2 exec`, `man 2 wait`, `man 2 shmget`, `man 2 semget`

---

## Assignment Submission

This repository contains all required files with student IDs appended to filenames as specified in the assignment requirements.

**Submitted by:**
- Student 1 (101276841)
- Student 2 (101116888)
