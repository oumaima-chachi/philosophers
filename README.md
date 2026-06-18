*This project has been created as part of the 42 curriculum by ochachi.*

# Philosophers

## Description

Philosophers is a project from the 42 curriculum designed to introduce multithreading and synchronization.

The goal is to solve the famous Dining Philosophers problem using threads and mutexes while avoiding data races, deadlocks, and starvation.

Each philosopher is represented by a thread and must alternate between eating, sleeping, and thinking while sharing forks with neighboring philosophers.

---

## Features

### Mandatory Part

* One thread per philosopher
* Mutex-protected forks
* Accurate timing management
* Death monitoring
* Thread synchronization
* Data race prevention
* Clean program termination

The simulation stops when:

* A philosopher dies
* Or all philosophers have eaten the required number of times (if specified)

---

## Compilation

```bash
make
```

Available commands:

```bash
make
make clean
make fclean
make re
```

---

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

Example with meal limit:

```bash
./philo 5 800 200 200 7
```

---

## Example Output

```text
0 1 is thinking
1 1 has taken a fork
2 1 has taken a fork
2 1 is eating
202 1 is sleeping
402 1 is thinking
```

---

## What I Learned

Through this project I learned:

* Multithreading with pthreads
* Mutexes and synchronization
* Race conditions
* Deadlock prevention
* Thread-safe programming
* Time management in concurrent systems
* Debugging concurrent applications

One of the most challenging parts was ensuring that philosophers could eat without causing deadlocks while also respecting the timing constraints of the subject.

---

## Technical Concepts

The project is based on:

* Threads (`pthread_create`)
* Mutexes (`pthread_mutex`)
* Shared resources
* Concurrent execution
* Monitoring threads
* Synchronization mechanisms

---

## Resources

* Dining Philosophers Problem
* POSIX Threads Documentation
* Linux pthread Manual
* 42 Resources

### AI Usage

AI tools were used to better understand concurrency concepts, mutex behavior, and synchronization strategies. Any generated information was reviewed, tested, and fully understood before being applied to the project.
