/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/08/15 13:34:54 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Loots of shit I think

	- DO I need 1 mutex for every thread? or 1 for all?
	- DO I need 1 cond for every thread? or 1 for all?
*/

long	print_n_update(char *s, int n, struct timeval *current_time, int token)
{
	long	precise_time;

	gettimeofday(current_time, NULL);
	precise_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000);
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

// int	is_one_dead(t_philo *ph)
// {
// 	pthread_mutex_lock(&ph->l.state_mutex);
// 	if (ph->l.is_dead)
// 		// return (1);
// 		return (pthread_mutex_unlock(&ph->l.state_mutex), 1);
// 	pthread_mutex_unlock(&ph->l.state_mutex);
// 	return (0);
// }
int is_he_dead(t_philo *ph, int n)
{
	static int status = 0;

	if (n)
	{
		// pthread_mutex_lock(&ph->l.state_mutex);
		status = 1;
		// pthread_mutex_unlock(&ph->l.state_mutex);
	}
	return (status);
}

void	*philo_diner_table(void *num)
{
	struct timeval	current_time;
	long			precise_time;
	t_philo			*ph;

	ph = (t_philo *)num;
	gettimeofday(&current_time, NULL);
	ph->dying_time = (current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000) + (ph->i.true_dying_time);
	while (!is_he_dead(ph, 0))
	{
		if (!eating_time(ph, &current_time))
			return (NULL);
		if (!sleeping_time(ph, &current_time))
			return (NULL);
		if (is_he_dead(ph, 0))
			return (NULL);

		pthread_mutex_lock(&ph->l.state_mutex);
		precise_time = print_n_update(0, 0, &current_time, 0);
		if (precise_time >= ph->dying_time)
		{
			// ph->l.is_dead = 1;
			is_he_dead(ph, 1);
			print_n_update("died", ph->id, &current_time, DIE);
			unlocker((void *[]){&ph->l.state_mutex, NULL});
			return (NULL);
		}
		pthread_mutex_unlock(&ph->l.state_mutex);
	}
	return (NULL);
}

int	thread_maker(t_init i)
{
	t_philo	*p;
	t_forks	f;
	t_lock	l;
	int		k;

	k = -1;
	p = NULL;
	f.forks = mem_manager(i.nbr_of_philo * sizeof(pthread_mutex_t), 0, 'A');
	f.nbr_of_philo = i.nbr_of_philo;
	while (++k < i.nbr_of_philo)
		if (pthread_mutex_init(&f.forks[k], NULL))
			return (1);
	k = -1;
	l.is_dead = 0;
	pthread_mutex_init(&l.state_mutex, NULL);
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&p, k, (void *[]){&f, &i, &l}))
			return (1);
	}
	joiner(p);
	pthread_mutex_destroy(&l.state_mutex);
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
