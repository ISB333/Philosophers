#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5

pthread_mutex_t	forks[NUM_PHILOSOPHERS];
pthread_t		philosophers[NUM_PHILOSOPHERS];

void	initialize_forks(void)
{
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}
}

void	*philosopher(void *num)
{
	int	id;
	int	left;
	int	right;

	id = *(int *)num;
	while (1)
	{
		// Think
		printf("Philosopher %d is thinking.\n", id);
		sleep(1);
		// Pick up forks
		left = id;
		right = (id + 1) % NUM_PHILOSOPHERS;
		pthread_mutex_lock(&forks[left]);
		pthread_mutex_lock(&forks[right]);
		// Eat
		printf("Philosopher %d is eating.\n", id);
		sleep(1);
		// Put down forks
		pthread_mutex_unlock(&forks[left]);
		pthread_mutex_unlock(&forks[right]);
		// Back to thinking
	}
}

int	main(void)
{
	int	ids[NUM_PHILOSOPHERS];

	initialize_forks();
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		ids[i] = i;
		pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
	}
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		pthread_join(philosophers[i], NULL);
	}
	return (0);
}
