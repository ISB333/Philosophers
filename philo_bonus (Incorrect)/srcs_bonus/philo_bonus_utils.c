/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:21:20 by adesille          #+#    #+#             */
/*   Updated: 2024/10/03 13:38:17 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	current_time;
	long			precise_time;

	gettimeofday(&current_time, NULL);
	precise_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (precise_time);
}

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(1);
}

void	unlinker(char *name[])
{
	while (*name)
		sem_unlink(*name++);
}

void	closer(void *name[])
{
	while (*name)
		sem_close(*name++);
}

void	killer(t_philo *ph)
{
	while (!check_death(ph))
		ft_usleep(1);
}
