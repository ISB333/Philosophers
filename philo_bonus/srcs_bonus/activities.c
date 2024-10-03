/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:42:21 by adesille          #+#    #+#             */
/*   Updated: 2024/10/03 14:18:55 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	update_death_time(t_philo *ph)
{
	sem_wait(ph->l->eat);
	if (check_death(ph))
		return (sem_post(ph->l->forks), sem_post(ph->l->forks), (void)0);
	ph->dying_time = get_time() - ph->start_time + ph->i.true_dying_time;
	sem_post(ph->l->eat);
	printer(ph, "is eating", ph->id, EAT);
	ft_usleep(ph->i.eating_time);
	if (ph->i.eating_counter != -1)
		ph->i.eating_counter--;
	sem_post(ph->l->forks);
	sem_post(ph->l->forks);
}

int	eating(t_philo *ph)
{
	if (!is_he_dead(ph))
	{
		if (ph->l->nbr_of_philo == 1)
		{
			printer(ph, "has taken a fork", ph->id, LEFT_FORK);
			return (killer(ph), 0);
		}
		if (ph->id % 2)
		{
			if(!is_he_dead(ph))
			{
				sem_wait(ph->l->forks);
				sem_wait(ph->l->forks);
				printer(ph, "has taken a fork", ph->id, LEFT_FORK);
				printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
				update_death_time(ph);
			}
		}
		else
		{
			if(!is_he_dead(ph))
			{
				sem_wait(ph->l->forks);
				sem_wait(ph->l->forks);
				printer(ph, "has taken a fork", ph->id, LEFT_FORK);
				printer(ph, "has taken a fork", ph->id, RIGHT_FORK);
				update_death_time(ph);
			}
		}
		return (1);
	}
	return (0);
}

int	printer(t_philo *ph, char *s, int n, int token)
{
	long	precise_time;

	sem_wait(ph->l->print);
	if (is_he_dead(ph))
		return (sem_post(ph->l->print), 0);
	precise_time = get_time() - ph->start_time;
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
	return (1);
}
