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

void	*sleeping(t_philo *ph)
{
	if (printer(ph, "sleeping.", ph->id, SLEEP))
		return (usleep(ph->i.sleeping_time), "YES");
	return (NULL);
}

void	*thinking(t_philo *ph)
{
	if (printer(ph, "is thinking.", ph->id, THINK))
		return ("YES");
	return (NULL);
}

void	update_death_time(t_philo *ph, struct timeval *current_time)
{
	if (is_he_dead(ph))
		return (sem_post(ph->l->forks), sem_post(ph->l->forks), (void)0);
	sem_wait(ph->l->eat);
	gettimeofday(current_time, NULL);
	ph->dying_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000) + (ph->i.true_dying_time);
	if (ph->i.eating_counter != -1)
		ph->i.eating_counter--;
	printer(ph, "is eating.", ph->id, EAT);
	usleep(ph->i.eating_time);
	sem_post(ph->l->forks);
	sem_post(ph->l->forks);
	sem_post(ph->l->eat);
}

void	*eating(t_philo *ph, struct timeval *current_time)
{
	if (!is_he_dead(ph))
	{
		sem_wait(ph->l->forks);
		printer(ph, "has taken left fork", ph->id, LEFT_FORK);
		if (ph->l->nbr_of_philo != 1)
		{
			sem_wait(ph->l->forks);
			printer(ph, "has taken right fork", ph->id, RIGHT_FORK);
			update_death_time(ph, current_time);
		}
		else
			sem_post(ph->l->forks);
	}
	return ("YES");
}

void	*printer(t_philo *ph, char *s, int n, int token)
{
	long	precise_time;

	if (is_he_dead(ph))
		return (NULL);
	sem_wait(ph->l->print);
	gettimeofday(&ph->l->current_time, NULL);
	precise_time = ((ph->l->current_time).tv_sec * 1000)
		+ ((ph->l->current_time).tv_usec / 1000);
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
	sem_post(ph->l->print);
	return ("YES");
}
