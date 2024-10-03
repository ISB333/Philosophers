/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:42:21 by adesille          #+#    #+#             */
/*   Updated: 2024/10/03 13:18:52 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *ph)
{
	if (printer(ph, "is sleeping", ph->id, SLEEP))
		return (ft_usleep(ph->i.sleeping_time), 1);
	return (0);
}

int	thinking(t_philo *ph)
{
	if (printer(ph, "is thinking", ph->id, THINK))
		return (1);
	return (0);
}

void	update_death_time(t_philo *ph, int left, int right)
{
	pthread_mutex_lock(&ph->l->m[EAT_MUTEX]);
	if (check_death(ph))
		return (unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right],
				&ph->l->m[EAT_MUTEX], NULL}), (void)0);
	ph->dying_time = get_time() - ph->start_time + (ph->i.true_dying_time);
	pthread_mutex_unlock(&ph->l->m[EAT_MUTEX]);
	printer(ph, "is eating", ph->id, EAT);
	ft_usleep(ph->i.eating_time);
	if (ph->i.eating_counter != -1)
		ph->i.eating_counter--;
	unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right], NULL});
}

int	eating_utils(t_philo *ph, int left, int right)
{
	if (!is_he_dead(ph))
	{
		pthread_mutex_lock(&ph->l->forks[right]);
		pthread_mutex_lock(&ph->l->forks[left]);
		printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
		printer(ph, "has taken a fork", ph->id, LEFT_FORK);
		update_death_time(ph, left, right);
		return (1);
	}
	return (0);
}

int	eating(t_philo *ph)
{
	int	left;
	int	right;

	left = ph->id;
	right = (ph->id + 1) % ph->l->nbr_of_philo;
	if (ph->id % 2 == 0)
	{
		if (!is_he_dead(ph))
		{
			if (ph->l->nbr_of_philo == 1)
			{
				printer(ph, "has taken a fork", ph->id, LEFT_FORK);
				return (killer(ph), 0);
			}
			pthread_mutex_lock(&ph->l->forks[left]);
			pthread_mutex_lock(&ph->l->forks[right]);
			printer(ph, "has taken a fork", ph->id, LEFT_FORK);
			printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
			update_death_time(ph, left, right);
			return (1);
		}
	}
	else
		return (eating_utils(ph, left, right));
	return (0);
}
