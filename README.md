# Dining Philosophers Simulation

## Overview
This project is a simulation of the classic **[Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)** implemented in C. The problem involves `N` philosophers sitting around a table, where each philosopher has one fork and a plate of spaghetti. To eat, a philosopher requires two forks, so they must wait for their neighbors to finish eating. The simulation includes time constraints: if a philosopher waits too long (more than `time_to_die`) without eating, they die, and the simulation stops.

Each philosopher is represented by a thread, and all philosophers must eat at least once before they die. The program simulates this scenario, ensuring that philosophers can eat while avoiding deadlock situations.

## How It Works
- **Philosophers and Forks**: Each philosopher has one fork, and a philosopher needs two forks to start eating.
- **Time Constraints**:
  - `time_to_eat`: The time a philosopher takes to eat.
  - `time_to_sleep`: The time a philosopher takes to sleep.
  - `time_to_die`: The maximum time a philosopher can wait without eating before they die.
- **Threads**: Each philosopher is represented by a separate thread, simulating the concurrent behavior of philosophers trying to eat.
- **Termination**: If any philosopher waits longer than `time_to_die` before getting the required forks, the philosopher dies, and the simulation halts.

## Features
- Multi-threaded simulation of philosophers using pthreads.
- Dynamically adjustable number of philosophers (`N`).
- Simulation terminates when a philosopher dies or after all philosophers have eaten at least   `number_of_times_each_philosopher_must_eat`.
- Fork sharing mechanism to avoid deadlock.
- Customizable time settings for `time_to_eat` and `time_to_die`.

## Compilation and Execution
### Requirements
- A C compiler (e.g., `gcc`).
- POSIX Threads (pthreads) library.

### Compilation and execution
To compile the program, use the following command:
```bash
  make
  ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> and optional parammeter <number_of_times_each_philosopher_must_eat>

