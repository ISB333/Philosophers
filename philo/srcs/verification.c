/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/09/30 14:24:05 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*unlocker(void **m)
{
	int	i;

	i = -1;
	while (m[++i])
		pthread_mutex_unlock((pthread_mutex_t *)m[i]);
	return (NULL);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_format(char *argv[])
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (argv[++i])
	{
		k = -1;
		while (argv[i][++k])
			if (!is_num(argv[i][k]))
				return (error("wrong format\n"), exit(EXIT_FAILURE));
	}
}

int	is_he_dead(t_philo *ph)
{
	int	status;

	pthread_mutex_lock(&ph->l->m[STATE_MUTEX]);
	status = ph->l->is_dead;
	pthread_mutex_unlock(&ph->l->m[STATE_MUTEX]);
	return (status);
}

int	check_death(t_philo *ph)
{
	long	precise_time;

	pthread_mutex_lock(&ph->l->m[STATE_MUTEX]);
	precise_time = get_time(&ph->l->current_time) - ph->l->start_time;
	// printf(ORANGE"%d precise = %ld\n%d dying = %ld\n"DEF, ph->id, precise_time, ph->id, ph->dying_time);
	if (precise_time >= ph->dying_time && !ph->l->is_dead)
	{
		pthread_mutex_lock(&ph->l->m[PRINT_MUTEX]);
		ph->l->is_dead = 1;
		printf(RED "%ld %d died\n" DEF, precise_time, ph->id);
		pthread_mutex_unlock(&ph->l->m[PRINT_MUTEX]);
		pthread_mutex_unlock(&ph->l->m[STATE_MUTEX]);
		return (1);
	}
	pthread_mutex_unlock(&ph->l->m[STATE_MUTEX]);
	return (0);
}
