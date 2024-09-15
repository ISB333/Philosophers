/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:42:21 by adesille          #+#    #+#             */
/*   Updated: 2024/09/09 12:45:10 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sleeping(t_philo *ph, struct timeval *current_time)
{
	if (printer(ph, "sleeping.", ph->id, current_time, SLEEP))
		return (usleep(ph->i.sleeping_time), "YES");
	return (NULL);
}

void	*thinking(t_philo *ph, struct timeval *current_time)
{
	if (printer(ph, "is thinking.", ph->id, current_time, THINK))
		return ("YES");
	return (NULL);
}

void	update_death_time(t_philo *ph, struct timeval *current_time, int left,
		int right)
{
	if (is_he_dead(ph))
		return ;
	pthread_mutex_lock(&ph->l->state_mutex);
	gettimeofday(current_time, NULL);
	ph->dying_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000) + (ph->i.true_dying_time);
	if (ph->i.eating_counter)
		ph->i.eating_counter--;
	pthread_mutex_unlock(&ph->l->state_mutex);
	printer(ph, "is eating.", ph->id, current_time, EAT);
	usleep(ph->i.eating_time);
	unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right], NULL});
}

void	*eating(t_philo *ph, struct timeval *current_time)
{
	int	left;
	int	right;

	left = ph->id;
	right = (ph->id + 1) % ph->l->nbr_of_philo;
	if (ph->id % 2 == 0)
	{
		if (!is_he_dead(ph))
		{
			pthread_mutex_lock(&ph->l->forks[left]);
			printer(ph, "has taken left fork", ph->id, current_time, LEFT_FORK);
			if (ph->l->nbr_of_philo != 1)
			{
				pthread_mutex_lock(&ph->l->forks[right]);
				printer(ph, "has taken right fork", ph->id, current_time,
					RIGHT_FORK);
				update_death_time(ph, current_time, left, right);
			}
			else
				pthread_mutex_unlock(&ph->l->forks[left]);
		}
	}
	else
	{
		if (!is_he_dead(ph))
		{
			pthread_mutex_lock(&ph->l->forks[right]);
			printer(ph, "has taken right fork", ph->id, current_time,
				RIGHT_FORK);
			pthread_mutex_lock(&ph->l->forks[left]);
			printer(ph, "has taken left fork", ph->id, current_time, LEFT_FORK);
			update_death_time(ph, current_time, left, right);
		}
	}
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
