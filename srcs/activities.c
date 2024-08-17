/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:42:21 by adesille          #+#    #+#             */
/*   Updated: 2024/08/17 10:47:12 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sleeping(t_philo *ph, struct timeval *current_time)
{
	if (is_he_dead(ph, 0))
		return (NULL);
	printer(ph, "sleeping.", ph->id, current_time, SLEEP);
	usleep(ph->i.sleeping_time);
	return ("YES");
}
void	*thinking(t_philo *ph, struct timeval *current_time)
{
	if (is_he_dead(ph, 0))
		return (NULL);
	printer(ph, "is thinking.", ph->id, current_time, THINK);
	return ("YES");
}

void	*eating(t_philo *ph, struct timeval *current_time)
{
	int	left;
	int	right;


	pthread_mutex_lock(&ph->l.eat_mutex);
	left = ph->id;
	right = (ph->id + 1) % ph->l.nbr_of_philo;

	if (ph->id % 2 == 0)
	{
		if (!is_he_dead(ph, 0))
		{
			pthread_mutex_lock(&ph->l.forks[left]);
			printer(ph, "has taken left fork", ph->id, current_time, LEFT_FORK);
		}
		if (!is_he_dead(ph, 0))
		{
			pthread_mutex_lock(&ph->l.forks[right]);
			printer(ph, "has taken right fork", ph->id, current_time, RIGHT_FORK);
		}
	}
	else
	{
		if (!is_he_dead(ph, 0))
		{
			pthread_mutex_lock(&ph->l.forks[right]);
			printer(ph, "has taken right fork", ph->id, current_time, RIGHT_FORK);
		}
		if (!is_he_dead(ph, 0))
		{
			pthread_mutex_lock(&ph->l.forks[left]);
			printer(ph, "has taken left fork", ph->id, current_time, LEFT_FORK);
		}
	}
	pthread_mutex_unlock(&ph->l.eat_mutex);
	
	if (is_he_dead(ph, 0))
		return (unlocker((void *[]){&ph->l.forks[left], &ph->l.forks[right], NULL}), NULL);

	pthread_mutex_lock(&ph->l.eat_mutex);
	gettimeofday(current_time, NULL);
	ph->dying_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000) + (ph->i.true_dying_time);
	printer(ph, "is eating.", ph->id, current_time, EAT);
	usleep(ph->i.eating_time);
	unlocker((void *[]){&ph->l.forks[left], &ph->l.forks[right],
		&ph->l.eat_mutex, NULL});
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
