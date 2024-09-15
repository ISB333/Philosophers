/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/09/09 12:48:43 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	update_time(struct timeval *current_time)
{
	long	precise_time;

	gettimeofday(current_time, NULL);
	precise_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000);
	return (precise_time);
}

void	*printer(t_philo *ph, char *s, int n, struct timeval *current_time,
		int token)
{
	long	precise_time;

	if (is_he_dead(ph))
		return (NULL);
	pthread_mutex_lock(&ph->l->state_mutex);
	gettimeofday(current_time, NULL);
	precise_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000);
	if (s)
	{
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
		printf("%ld %d %s\n" DEF, precise_time, n, s);
	}
	pthread_mutex_unlock(&ph->l->state_mutex);
	return ("YES");
}

void	*philo_diner_table(void *num)
{
	t_philo	*ph;

	ph = (t_philo *)num;
	while (!is_he_dead(ph) && ph->i.eating_counter)
	{
		if (check_death(ph) || !eating(ph, &ph->l->current_time))
			return (NULL);
		if (check_death(ph) || !thinking(ph, &ph->l->current_time))
			return (NULL);
		if (check_death(ph) || !sleeping(ph, &ph->l->current_time))
			return (NULL);
	}
	return (NULL);
}

int	thread_maker(t_init i)
{
	t_philo	*ph;
	t_lock	l;
	int		k;

	k = -1;
	ph = NULL;
	l.forks = mem_manager(i.nbr_of_philo * sizeof(pthread_mutex_t), ALLOCATE);
	l.nbr_of_philo = i.nbr_of_philo;
	while (++k < i.nbr_of_philo)
		if (pthread_mutex_init(&l.forks[k], NULL))
			return (1);
	k = -1;
	l.is_dead = 0;
	pthread_mutex_init(&l.state_mutex, NULL);
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&ph, k, &i, &l))
			return (1);
	}
	joiner(ph);
	pthread_mutex_destroy(&l.state_mutex);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_init	i;

	if (argc == 5 || argc == 6)
	{
		check_format(argv);
		parsing(&i, argv);
		thread_maker(i);
	}
	else
		return (error("wrong number of arguments\n"), 1);
	printf("-----------------------------\n\n");
	return (mem_manager(0, FREE_MEMORY), 0);
}
