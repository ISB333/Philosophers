/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:15:44 by adesille          #+#    #+#             */
/*   Updated: 2024/10/04 09:42:01 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	current_time;
	long			precise_time;

	gettimeofday(&current_time, NULL);
	precise_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (precise_time);
}

void	*unlocker(void **m)
{
	int	i;

	i = -1;
	while (m[++i])
		pthread_mutex_unlock((pthread_mutex_t *)m[i]);
	return (NULL);
}

void	mutex_destroyer(t_lock *l)
{
	int	k;

	k = -1;
	while (++k < 3)
		pthread_mutex_destroy(&(*l).m[k]);
}

void	killer(t_philo *ph)
{
	while (!check_death(ph))
		ft_usleep(10);
}

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(1);
}
