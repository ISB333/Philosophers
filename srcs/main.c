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

void	printer(t_philo *ph, char *s, int n, struct timeval *current_time, int token)
{
	long	precise_time;

	pthread_mutex_lock(&ph->l.print_mutex);
	if (is_he_dead(ph))
	{
		pthread_mutex_unlock(&ph->l.print_mutex);
		return ;
	}
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
		printf("%ld %d %s\n"DEF, precise_time, n, s);
	}
	pthread_mutex_unlock(&ph->l.print_mutex);
}

int is_he_dead(t_philo *ph)
{
	int			status;

	pthread_mutex_lock(&ph->l.death_check_mutex);
	status = ph->l.is_dead;
	pthread_mutex_unlock(&ph->l.death_check_mutex);
	return (status);
}

void	*philo_diner_table(void *num)
{
	long			precise_time;
	t_philo			*ph;

	ph = (t_philo *)num;
	while (1)
	{
		if (!eating(ph, &ph->l.current_time))
			return (NULL);
		if (!thinking(ph, &ph->l.current_time))
			return (NULL);
		if (!sleeping(ph, &ph->l.current_time))
			return (NULL);
		if (is_he_dead(ph))
			return (NULL);

		pthread_mutex_lock(&ph->l.death_mutex);
		precise_time = update_time(&ph->l.current_time);
		if (precise_time >= ph->dying_time && !ph->l.is_dead)
		{
			// pthread_mutex_lock(&ph->l.sleep_mutex);
			// pthread_mutex_lock(&ph->l.eat_mutex);
			ph->l.is_dead = 1;
			printf(RED"%ld %d died\n"DEF, precise_time, ph->id);
			// pthread_mutex_unlock(&ph->l.sleep_mutex);
			// pthread_mutex_unlock(&ph->l.eat_mutex);
			pthread_mutex_unlock(&ph->l.death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->l.death_mutex);
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
	l.forks = mem_manager(i.nbr_of_philo * sizeof(pthread_mutex_t), 0, 'A');
	l.nbr_of_philo = i.nbr_of_philo;
	while (++k < i.nbr_of_philo)
		if (pthread_mutex_init(&l.forks[k], NULL))
			return (1);
	k = -1;
	l.is_dead = 0;
	pthread_mutex_init(&l.eat_mutex, NULL);
	pthread_mutex_init(&l.print_mutex, NULL);
	pthread_mutex_init(&l.sleep_mutex, NULL);
	pthread_mutex_init(&l.death_mutex, NULL);
	pthread_mutex_init(&l.death_check_mutex, NULL);
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&ph, k, i, l))
			return (1);
	}
	joiner(ph);
	pthread_mutex_destroy(&l.eat_mutex);
	pthread_mutex_destroy(&l.print_mutex);
	pthread_mutex_destroy(&l.sleep_mutex);
	pthread_mutex_destroy(&l.death_mutex);
	pthread_mutex_destroy(&l.death_check_mutex);
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
