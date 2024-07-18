/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/07/18 08:46:15 by isb3             ###   ########.fr       */
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

static	int is_philo_dead(int n)
{
	static int y_or_no = 0;

	if (n)
		y_or_no = 1;
	return (y_or_no);
}

// int	death_protect()
// {

// }

void	*unlocker(void **m)
{
	int i = -1;

	while (m[++i])
		pthread_mutex_unlock((pthread_mutex_t *)m[i]);
	return (NULL);
}

void	*sleeping_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->f.state_mutex);
	if (is_philo_dead(0))
		return (unlocker((void *[]){&ph->f.state_mutex, NULL}));
	pthread_mutex_unlock(&ph->f.state_mutex);
	printf("Philosopher %d is sleeping.\n", ph->id);
	usleep(ph->i.sleeping_time);
	pthread_mutex_lock(&ph->f.state_mutex);
	if (is_philo_dead(0))
		return (unlocker((void *[]){&ph->f.state_mutex, NULL}));
	pthread_mutex_unlock(&ph->f.state_mutex);
	return ("YES");
}

void	*eating_time(t_philo *ph, struct timeval *current_time)
{
	int	left;
	int	right;

	printf("Philosopher %d is thinking.\n", ph->id);
	left = ph->id;
	right = (ph->id + 1) % ph->f.nbr_of_philo;
	pthread_mutex_lock(&ph->f.forks[left]);
	pthread_mutex_lock(&ph->f.forks[right]);
	gettimeofday(current_time, NULL);
	ph->dying_time = (*current_time).tv_usec + ph->i.true_dying_time;
	// printf(BLUE"philo %d dying time = %ld\n"DEF, ph->id, ph->dying_time);
	pthread_mutex_lock(&ph->f.state_mutex);
	if (is_philo_dead(0))
		return (unlocker((void *[]){&ph->f.state_mutex, &ph->f.forks[left],
				&ph->f.forks[right], NULL}));
	pthread_mutex_unlock(&ph->f.state_mutex);

	// printf(GREEN"time of the day %ld\n"DEF, current_time.tv_usec);
	printf("Philosopher %d is eating.\n", ph->id);
	usleep(ph->i.eating_time);
	unlocker((void *[]){&ph->f.forks[left], &ph->f.forks[right], NULL});
	return ("YES");
}

void	*philo_diner_table(void *num)
{
	struct timeval current_time;
	t_philo	*ph;

	ph = (t_philo *)num;
	gettimeofday(&current_time, NULL);
	ph->dying_time = current_time.tv_usec + ph->i.true_dying_time;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		if (current_time.tv_usec >= ph->dying_time)
		{
			pthread_mutex_lock(&ph->f.state_mutex);
			is_philo_dead(1);
			pthread_cond_broadcast(&ph->f.state_cond);
			printf(RED"Philosopher %d is DEAD.\n"DEF, ph->id);
			return (unlocker((void *[]){&ph->f.state_mutex, NULL}));
		}

		pthread_mutex_lock(&ph->f.state_mutex);
        if (is_philo_dead(0))
			return (unlocker((void *[]){&ph->f.state_mutex, NULL}));
        pthread_mutex_unlock(&ph->f.state_mutex);

		if (!eating_time(ph, &current_time))
			return (NULL);
	
		if (!sleeping_time(ph))
			return (NULL);
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
	pthread_mutex_init(&f.state_mutex, NULL);
	pthread_cond_init(&f.state_cond, NULL);
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&p, k, f, i))
			return (1);
	}
	joiner(p);

    pthread_mutex_destroy(&f.state_mutex);
    pthread_cond_destroy(&f.state_cond);

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
