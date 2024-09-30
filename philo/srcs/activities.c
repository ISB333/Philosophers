/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:42:21 by adesille          #+#    #+#             */
/*   Updated: 2024/09/30 16:50:33 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_usleep(t_philo *ph, long time_to_sleep)
// {
// 	long time;
// 	long precise_time;

// 	time = get_time(&ph->l->current_time) - ph->l->start_time + time_to_sleep;
// 	precise_time = get_time(&ph->l->current_time) - ph->l->start_time;
// 	// printf("%ld\n%ld\n", time, precise_time);
// 	while (precise_time < time)
// 	{
// 		usleep(1);
// 		precise_time = get_time(&ph->l->current_time) - ph->l->start_time;
// 	}
// }

int	sleeping(t_philo *ph)
{
	if (printer(ph, "is sleeping", ph->id, SLEEP))
	{
		usleep(ph->i.sleeping_time * 1000);
		return (1);
	}
	return (0);
}

int	thinking(t_philo *ph)
{
	if (printer(ph, "is thinking", ph->id, THINK))
		return (1);
	return (0);
}

void	update_death_time(t_philo *ph, struct timeval *current_time, int left,
		int right)
{
	if (is_he_dead(ph))
	{
		unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right], NULL});
		return ;
	}
	pthread_mutex_lock(&ph->l->m[EAT_MUTEX]);
	// printer(ph, "is eating.", ph->id, EAT);
	// if (check_death(ph))
	// 	return (unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right], &ph->l->m[EAT_MUTEX], NULL}), (void)0);
	printer(ph, "is eating", ph->id, EAT);
	usleep(ph->i.eating_time * 1000);
	if ((get_time(&ph->l->current_time) - ph->l->start_time) > ph->dying_time && !ph->l->is_dead)
	{
		pthread_mutex_lock(&ph->l->m[STATE_MUTEX]);
		pthread_mutex_lock(&ph->l->m[PRINT_MUTEX]);
		ph->l->is_dead = 1;
		printf(RED "%ld %d is died\n" DEF, get_time(&ph->l->current_time) - ph->l->start_time, ph->id);
		pthread_mutex_unlock(&ph->l->m[PRINT_MUTEX]);
		pthread_mutex_unlock(&ph->l->m[STATE_MUTEX]);
		unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right], &ph->l->m[EAT_MUTEX], NULL});
		return ;
	}
	ph->dying_time = get_time(&ph->l->current_time) - ph->l->start_time + ph->i.true_dying_time;
	// gettimeofday(current_time, NULL);
	// printf("%d dying = %ld\n", ph->id, ph->dying_time);
	// ph->dying_time += ph->i.true_dying_time;
	if (ph->i.eating_counter != -1)
		ph->i.eating_counter--;
	unlocker((void *[]){&ph->l->forks[left], &ph->l->forks[right],
		&ph->l->m[EAT_MUTEX], NULL});
}

int	eating_utils(t_philo *ph, int left, int right)
{
	if (!is_he_dead(ph))
	{
		pthread_mutex_lock(&ph->l->forks[right]);
		// printer(ph, "has taken right fork", ph->id, RIGHT_FORK);
		printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
		pthread_mutex_lock(&ph->l->forks[left]);
		// printer(ph, "has taken left fork", ph->id, LEFT_FORK);
		printer(ph, "has taken a fork", ph->id, LEFT_FORK);
		update_death_time(ph, &ph->l->current_time, left, right);
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
	if (ph->id % 2)
	{
		if (!is_he_dead(ph))
		{
			pthread_mutex_lock(&ph->l->forks[left]);
			// printer(ph, "has taken left fork", ph->id, LEFT_FORK);
			printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
			if (ph->l->nbr_of_philo != 1)
			{
				pthread_mutex_lock(&ph->l->forks[right]);
				// printer(ph, "has taken right fork", ph->id, RIGHT_FORK);
				printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
				update_death_time(ph, &ph->l->current_time, left, right);
			}
			else
				return (killer(ph, left), 0);
			return (1);
		}
	}
	else
		return (eating_utils(ph, left, right));
	return (0);
}
