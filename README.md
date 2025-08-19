## Philosophers - 42

# Description:
Philosophers is about concurrent programming through the "Dining Philosophers Problem." The project simulates philosophers sitting around a table who alternately eat, think, and sleep. Each philosopher needs two forks to eat, but there are only as many forks as philosophers, creating potential deadlock situations. The challenge lies in preventing philosophers from starving while avoiding race conditions, deadlocks, and data races. This project teaches fundamental concepts of multithreading, process synchronization, and resource sharing. You need to implement precise timing mechanisms and ensure thread safety while maintaining optimal performance and preventing any philosopher from dying of starvation.

# Context:
Part of 42 Common Core.

# Main Technologies / Skills Used:

- **Programming Languages:** C
- **Multithreading:** Creating and managing multiple threads using "pthread_create", "pthread_join", "pthread_detach"
- **Mutex Synchronization:** Implementing thread-safe resource access with pthread_mutex_lock/unlock
- **Deadlock Prevention:** Designing algorithms to avoid circular waiting and resource conflicts
- **Race Condition Management:** Ensuring thread-safe access to shared resources and variables
- **Timing and Precision:** Implementing precise millisecond timing with gettimeofday and usleep
- **Concurrent Algorithm Design:** Developing strategies to prevent starvation and ensure fairness
- **Memory Management:** Safe allocation and cleanup in multithreaded environments
- **Error Handling:** Managing thread creation failures and synchronization errors

# Installation and compilation
1. Clone this repository into your project:
```bash
git clone git@github.com:lukifight73/Philosophers-42.git
```
2. Run the following command:
```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
For example to see the philosophers simulation in action with 5 philosophers, where each philosopher dies if they do not eat within 800ms, takes 200ms to eat, and sleeps for 100ms.
```bash
./philo 5 800 200 100
```
