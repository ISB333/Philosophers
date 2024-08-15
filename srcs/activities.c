/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:42:21 by adesille          #+#    #+#             */
/*   Updated: 2024/08/15 12:42:22 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sleeping_time(t_philo *ph, struct timeval *current_time)
{
	if (is_one_dead(ph))
		return (NULL);
	print_n_update("sleeping.", ph->id, current_time, SLEEP);
	usleep(ph->i.sleeping_time);
	return ("YES");
}

void	*eating_time(t_philo *ph, struct timeval *current_time)
{
	int	left;
	int	right;

	if (is_one_dead(ph))
		return (NULL);

	print_n_update("is thinking.", ph->id, current_time, THINK);
	left = ph->id;
	right = (ph->id + 1) % ph->f.nbr_of_philo;

	if (ph->id % 2 == 0 && !is_one_dead(ph))
	{
		pthread_mutex_lock(&ph->f.forks[left]);
		print_n_update("has taken left fork", ph->id, current_time, LEFT_FORK);
		pthread_mutex_lock(&ph->f.forks[right]);
		print_n_update("has taken right fork", ph->id, current_time, RIGHT_FORK);
	}
	else if (!is_one_dead(ph))
	{
		pthread_mutex_lock(&ph->f.forks[right]);
		print_n_update("has taken right fork", ph->id, current_time, RIGHT_FORK);
		pthread_mutex_lock(&ph->f.forks[left]);
		print_n_update("has taken left fork", ph->id, current_time, LEFT_FORK);
	}
	
	if (is_one_dead(ph))
		return (unlocker((void *[]){&ph->f.forks[left], &ph->f.forks[right], NULL}), NULL);

	pthread_mutex_lock(&ph->l.state_mutex);
	gettimeofday(current_time, NULL);
	ph->dying_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000) + (ph->i.true_dying_time);
	print_n_update("is eating.", ph->id, current_time, EAT);
	usleep(ph->i.eating_time);
	unlocker((void *[]){&ph->f.forks[left], &ph->f.forks[right],
		&ph->l.state_mutex, NULL});
	return ("YES");
}

void	*unlocker(void **m)
{
	int	i;

	i = -1;
	while (m[++i])
		pthread_mutex_unlock((pthread_mutex_t *)m[i]);
	return (NULL);
}
