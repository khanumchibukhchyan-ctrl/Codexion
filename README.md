# Codexion
*This project has been created as part of the 42 curriculum by kchibukh.*

---

## Description

Codexion is a multithreaded C project based on synchronization and scheduling.

The program simulates a group of coders working with a limited number of shared resources called **dongles**.

Each coder is represented by a thread. Coders need dongles to perform their work, and several coders may compete for the same resources.

The main goal of the project is to correctly manage concurrency while avoiding:

* race conditions;
* deadlocks;
* starvation;
* incorrect resource allocation;
* incorrect scheduling;
* data races when accessing shared data.

The project uses the POSIX Threads (`pthread`) library.

---
## Project Goal

The goal of the Codexion project is to develop a multithreaded simulation in C using POSIX threads.

The project focuses on understanding and correctly implementing:

* Thread creation and management
* Mutexes and condition variables
* Synchronization between threads
* Shared resource management
* Scheduling algorithms such as FIFO and EDF
* Deadlock prevention
* Starvation prevention
* Time and deadline management
* Safe memory management

The main challenge is to allow multiple coders to work concurrently while safely sharing a limited number of dongles.

The program must remain synchronized and predictable even when multiple threads request the same resources at the same time.

---

## Compilation

To compile the project, use:

```bash
make
```

The project must be compiled with POSIX thread support.

You can also compile it manually with:

```bash
cc -Wall -Wextra -Werror -pthread *.c -o codexion
```

After successful compilation, the executable can be launched with:

```bash
./codexion [arguments]
```

Use the arguments required by the project subject to configure the simulation.

### Makefile rules

- make / make all  
- make clean  
- make fclean  
- make re  

## Concepts

The project requires understanding of:

* threads;
* mutexes;
* condition variables;
* synchronization;
* shared resources;
* deadlocks;
* starvation;
* scheduling algorithms;
* timestamps and deadlines;
* FIFO scheduling;
* EDF (Earliest Deadline First);
* dynamic data structures;
* thread-safe access to shared data.

---

## Program Model

The simulation contains two main entities.

### Coder

Each coder is executed by its own thread.

A coder has information such as:

* an ID;
* the number of successful compilations;
* the last compilation time;
* a deadline;
* its thread;
* links to other coders;
* a reference to the simulation.

Example structure:

```c
typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile_time;
	long			deadline;
	pthread_t		thread;
	struct s_coder	*left;
	struct s_coder	*right;
	struct s_sim	*sim;
}	t_coder;
```

### Dongle

A dongle is a shared resource.

A coder must acquire the required dongles before performing an operation.

A dongle contains:

* an ID;
* its availability;
* a cooldown timestamp;
* a mutex protecting the dongle;
* a condition variable used to wait for the dongle.

Example:

```c
typedef struct s_dongle
{
	int				id;
	int				available;
	long			cooldown_until;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;
```

---

## Threads

Each coder runs in a separate thread.

The main thread is responsible for:

1. parsing the arguments;
2. initializing the simulation;
3. creating the coder threads;
4. starting the simulation;
5. monitoring the simulation;
6. waiting for the coder threads;
7. cleaning up all allocated resources.

A coder thread repeatedly performs its assigned work while the simulation is running.

---

## Synchronization

Because multiple threads access shared resources, synchronization is necessary.

### Mutex

A mutex provides exclusive access to shared data.

Only one thread can hold a mutex at a time.

Typical usage:

```c
pthread_mutex_lock(&dongle->mutex);

/* access shared data */

pthread_mutex_unlock(&dongle->mutex);
```

The mutex prevents two coders from modifying the same resource simultaneously.

---

### Condition Variable

A condition variable allows a thread to sleep until a particular condition becomes true.

For example, if a dongle is currently unavailable, a coder should not continuously check it in a busy loop.

Instead, it can wait:

```c
pthread_cond_wait(&dongle->cond, &dongle->mutex);
```

When the dongle becomes available, another thread can wake waiting threads with:

```c
pthread_cond_signal(&dongle->cond);
```

or:

```c
pthread_cond_broadcast(&dongle->cond);
```

---

## Scheduling

The project requires managing which coder should receive access to resources.

Two important scheduling strategies are:

### FIFO

FIFO means:

> First In, First Out.

The coder that has been waiting the longest gets priority.

This provides a simple and predictable scheduling strategy.

---

### EDF

EDF means:

> Earliest Deadline First.

The coder with the closest deadline receives priority.

For example:

```text
Coder 1 -> deadline 5000
Coder 2 -> deadline 3000
Coder 3 -> deadline 7000
```

EDF chooses:

```text
Coder 2
```

because its deadline is the earliest.

---

## Deadlocks

A deadlock happens when threads wait for resources held by each other.

For example:

```text
Coder A owns Dongle 1
Coder B owns Dongle 2

Coder A waits for Dongle 2
Coder B waits for Dongle 1
```

Neither coder can continue.

The implementation must therefore be designed to avoid deadlocks.

Possible techniques include:

* consistent resource ordering;
* controlled acquisition of resources;
* releasing resources correctly;
* using condition variables;
* scheduling access to shared resources.

---

## Starvation

Starvation occurs when a coder continuously waits while other coders repeatedly receive resources.

For example:

```text
Coder A -> waiting
Coder B -> gets resource
Coder C -> gets resource
Coder B -> gets resource again
Coder C -> gets resource again
...
Coder A -> never gets resource
```

The scheduling mechanism should prevent a coder from being ignored indefinitely.

FIFO can help provide fairness, while EDF prioritizes deadlines.

---

## Time Management

The simulation uses timestamps to determine:

* when a coder started working;
* when a coder last compiled;
* when a deadline expires;
* when a dongle becomes available again;
* how long a coder has been waiting.

Functions such as:

```c
gettimeofday()
clock_gettime()
usleep()
```

can be used for time measurement and delays.

The implementation should use a consistent time unit throughout the program.

---

## Main Simulation Flow

The general execution flow is:

```text
Program starts
      |
      v
Parse arguments
      |
      v
Initialize simulation
      |
      v
Initialize coders
      |
      v
Initialize dongles
      |
      v
Create coder threads
      |
      v
Start simulation
      |
      v
Coders request resources
      |
      v
Scheduler selects coders
      |
      v
Coder acquires dongles
      |
      v
Coder performs compilation
      |
      v
Coder releases dongles
      |
      v
Simulation continues
      |
      v
Stop condition reached
      |
      v
Join threads
      |
      v
Destroy mutexes/conditions
      |
      v
Free memory
      |
      v
Exit
```

---

## Error Handling

The program should correctly handle invalid input and system errors.

Examples include:

* invalid number of arguments;
* invalid numeric values;
* allocation failure;
* `pthread_create()` failure;
* `pthread_join()` failure;
* mutex initialization failure;
* condition variable initialization failure;
* invalid simulation parameters.

The program should not continue execution after a critical initialization failure.

---

## Memory Management

Every dynamically allocated object must eventually be freed.

The program must clean up:

* coders;
* dongles;
* simulation structures;
* dynamically allocated arrays;
* mutexes;
* condition variables;
* threads.

The general cleanup order should ensure that no thread is still using an object before that object is destroyed.

---

## Compilation

Compile the project using:

```bash
make
```

For a manual compilation:

```bash
cc -Wall -Wextra -Werror -pthread *.c -o codexion
```

The `-pthread` option is required because the project uses POSIX threads.

---

## Execution

The program is executed according to the parameters specified by the project subject.

Example:

```bash
./codexion ...
```

Run the program with the required arguments for the desired simulation configuration.

---

## Recommended Project Structure

A possible project structure is:

```text
codexion/
├── Makefile
├── README.md
├── includes/
│   └── codexion.h
└── src/
    ├── main.c
    ├── init.c
    ├── parsing.c
    ├── simulation.c
    ├── coder.c
    ├── dongle.c
    ├── scheduler.c
    ├── fifo.c
    ├── edf.c
    ├── monitor.c
    ├── time.c
    └── cleanup.c
```

The exact file organization can be adapted to the implementation.

---

## Allowed Functions

The project relies on POSIX threading and timing functions such as:

```c
pthread_create()
pthread_join()

pthread_mutex_init()
pthread_mutex_lock()
pthread_mutex_unlock()
pthread_mutex_destroy()

pthread_cond_init()
pthread_cond_wait()
pthread_cond_timedwait()
pthread_cond_signal()
pthread_cond_broadcast()
pthread_cond_destroy()

gettimeofday()
clock_gettime()
usleep()

fprintf()
```

---

## Important Rules

The implementation should guarantee:

* no data races;
* no deadlocks;
* no uncontrolled busy waiting;
* correct mutex usage;
* correct condition-variable usage;
* correct thread termination;
* correct resource release;
* correct memory cleanup;
* deterministic and understandable scheduling behavior.

---

## Goal

The main objective of Codexion is to understand how to build a safe concurrent program in C.

The project combines:

```text
C
+
POSIX Threads
+
Mutexes
+
Condition Variables
+
Scheduling
+
Resource Management
+
Time Management
+
Deadlock Prevention
```

Understanding these concepts is more important than simply making the program compile: the simulation must remain correct when many threads compete for the same resources.
