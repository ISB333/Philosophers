/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/08/14 12:00:16 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	? To return a value, we should malloc an int * to store the value we want to return, then cast it to (void *)
	e.g :
		if (pthread_join(th, (void**) &res) != 0)
		*in the routine*:
		*result = value;
		return (void*) result;

	* 1- Philosophers eat with right & left forks
	* 2- Finished eating, put his forks back on the table
	* 3- Sleep
	* 4- Wake-up & Think

	! Conditions :
		! - fork = nbr_of_philo / 2 (1 if 1 nbr_of_philo)
		! - Each philosopher has a fork on their left and their right
		! - Each philosopher has a number from 1 to nbr_of_philo
			! -> Philo 1 sits next to nbr_of_philo
		! - To prevent philosophers from duplicating forks, 
			! you should protect the forks state with a mutex for each of them

		! - They should never die starving
		! - They don't speak to each other
		! - They don't know if another is about to die
*/

long	print_n_update(char *s, int n, struct timeval *current_time, int token)
{
	long precise_time;
	gettimeofday(current_time, NULL);
	precise_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec / 1000);
	if (s)
	{
		// if (THINK)
			// printf(de
		if (token == EAT)
			printf(GREEN);
		if (token == SLEEP)
			printf(BLUE);
		if (token == DIE)
			printf(RED);
		if (token == LEFT_FORK)
			printf(YELLOW);
		if (token == RIGHT_FORK)
			printf(YELLOW);
			// printf(ORANGE);
		printf("%ld %d %s\n", precise_time, n, s);
		printf(DEF);
	}
	return (precise_time);
}

void set_philo_dead(t_philo *ph)
{
    pthread_mutex_lock(&ph->manager.mutex);
    ph->manager.any_philo_dead = 1;
    pthread_cond_broadcast(&ph->manager.cond); // Notify all threads
    pthread_mutex_unlock(&ph->manager.mutex);
}


void	*philo_diner_table(void *num)
{
	struct timeval current_time;
	long	precise_time;
	t_philo	*ph;

	ph = (t_philo *)num;
	gettimeofday(&current_time, NULL);
	ph->dying_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) + (ph->i.true_dying_time);
	while (1)
	{
		pthread_mutex_lock(&ph->state_mutex);
        while (ph->is_dead) {
            pthread_mutex_unlock(&ph->state_mutex);
            return NULL; // Exit if any philosopher is dead
        }
        pthread_mutex_unlock(&ph->state_mutex);

		// if (is_philo_dead(0, ph))
		// 	return (pthread_mutex_unlock(&ph->f.state_mutex), NULL);
		if (!eating_time(ph, &current_time) || !sleeping_time(ph, &current_time))
			return (NULL);
			// return (pthread_mutex_unlock(&ph->f.state_mutex), NULL);

		pthread_mutex_lock(&ph->state_mutex);
		precise_time = print_n_update(0, 0, &current_time, 0);
		if (precise_time >= ph->dying_time)
		{
			// is_philo_dead(1, ph);
			set_philo_dead(ph);
			print_n_update("died", ph->id, &current_time, DIE);
			unlocker((void *[]){&ph->state_mutex, NULL});
			return (NULL);
		}
        pthread_mutex_unlock(&ph->state_mutex);
	}
	return (NULL);
}

int	thread_maker(t_init i)
{
	t_philo	*p;
	t_forks f;
	int k = -1;

	p = NULL;
    pthread_cond_init(&man.cond, NULL);

	f.forks = mem_manager(i.nbr_of_philo * sizeof(pthread_mutex_t), 0, 'A');
	f.nbr_of_philo = i.nbr_of_philo;
	while (++k < i.nbr_of_philo)
		if (pthread_mutex_init(&f.forks[k], NULL))
			return (1);
	k = -1;
	pthread_mutex_init(&state_mutex, NULL);
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&p, k, f, i, man))
			return (1);
	}
	joiner(p);

    pthread_mutex_destroy(&f.state_mutex);
	pthread_cond_destroy(&man.cond);

	return (0);
}

int	main(int argc, char *argv[])
{
	t_init	i;

	if (argc == 5 || argc == 6)
	{
		parsing(&i, argv);
		thread_maker(i);
	}
	else
		return (error("wrong number of arguments\n"), 1);
	printf("-----------------------------\n\n");
	return (mem_manager(0, 0, 'C'), 0);
}
