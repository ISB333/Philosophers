#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t *forks;

void philosopher_life(int id) {
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);

        // Take two forks (decrement semaphore)
        sem_wait(forks);
        sem_wait(forks);

        // Eating
        printf("Philosopher %d is eating\n", id);
        sleep(1);  // Simulate eating time

        // Put down forks (increment semaphore)
        sem_post(forks);
        sem_post(forks);

        // Sleeping
        printf("Philosopher %d is sleeping\n", id);
        sleep(1);  // Simulate sleeping time
    }
}

int main() {
    pid_t philosopher_pids[NUM_PHILOSOPHERS];

    // Initialize semaphore with NUM_PHILOSOPHERS forks
    forks = sem_open("/forks_semaphore", O_CREAT, 0644, NUM_PHILOSOPHERS);
    if (forks == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    // Create philosopher processes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_pids[i] = fork();
        if (philosopher_pids[i] == 0) {
            philosopher_life(i + 1);  // Child process
            exit(0);  // Make sure philosopher process exits cleanly
        }
    }

    // Monitor philosopher processes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        waitpid(philosopher_pids[i], NULL, 0);
    }

    // Clean up semaphore
    sem_close(forks);
    sem_unlink("/forks_semaphore");

    return 0;
}
