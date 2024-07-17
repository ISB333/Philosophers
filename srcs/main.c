/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/07/17 10:53:47 by isb3             ###   ########.fr       */
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

void	*philosopher(void *num)
{
	struct timeval current_time;
	t_philo	*ph;
	int	left;
	int	right;

	ph = (t_philo *)num;
	gettimeofday(&current_time, NULL);
	ph->dying_time = current_time.tv_usec + ph->i.true_dying_time;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec >= ph->dying_time)
		{
			printf(RED"Philosopher %d is DEAD.\n"DEF, ph->id);
			break ;
		}
		printf("Philosopher %d is thinking.\n", ph->id);
		left = ph->id;
		right = (ph->id + 1) % ph->f.nbr_of_philo;

		pthread_mutex_lock(&ph->f.forks[left]);
		pthread_mutex_lock(&ph->f.forks[right]);
		gettimeofday(&current_time, NULL);
		ph->dying_time = current_time.tv_usec + ph->i.true_dying_time;
		printf(BLUE"philo %d dying time = %ld\n"DEF, ph->id, ph->dying_time);
		printf(GREEN"time of the day %ld\n"DEF, current_time.tv_usec);
		printf("Philosopher %d is eating.\n", ph->id);
		usleep(ph->i.eating_time);
		// sleep(1);
	
		pthread_mutex_unlock(&ph->f.forks[left]);
		pthread_mutex_unlock(&ph->f.forks[right]);
		printf("Philosopher %d is sleeping.\n", ph->id);
		usleep(ph->i.sleeping_time);
		// sleep(1);
	}
	return (NULL);
}

int	thread_maker(t_init i)
{
	t_philo	*p;
	t_forks f;
	int k = -1;

	p = NULL;
	f.forks = mem_manager(i.nbr_of_philo * sizeof(pthread_mutex_t), 0, 'A');
	f.nbr_of_philo = i.nbr_of_philo;
	while (++k < i.nbr_of_philo)
		if (pthread_mutex_init(&f.forks[k], NULL))
			return (1);
	k = -1;
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&p, k, f, i))
			return (1);
	}
	joiner(p);
	// pthread_mutex_destroy(f.forks);
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
	return (0);
}
