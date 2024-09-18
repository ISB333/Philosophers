/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/09/09 12:48:43 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(struct timeval *current_time)
{
	long	precise_time;

	gettimeofday(current_time, NULL);
	precise_time = ((*current_time).tv_sec * 1000) + ((*current_time).tv_usec
			/ 1000);
	return (precise_time);
}

void	*philo_diner_table(t_philo *ph)
{
	while (!is_he_dead(ph) && ph->i.eating_counter)
	{
		if (check_death(ph) || !eating(ph, &ph->l->current_time))
			return (NULL);
		if (check_death(ph) || !thinking(ph))
			return (NULL);
		if (check_death(ph) || !sleeping(ph))
			return (NULL);
	}
	return (NULL);
}

void	execution(t_philo *ph, t_lock l)
{
	int	k;

	while (ph)
	{
		ph->pid = fork();
		if (!ph->pid)
		{
			philo_diner_table(ph);
			mem_manager(0, FREE_MEMORY);
			unlinker((char *[]){"/forks", "/state", "/eat", "print", NULL});
			closer((void *[]){l.forks, l.state, l.eat, l.print, NULL});
			kill(0, SIGKILL);
		}
		ph = ph->next;
	}
	k = -1;
	while (++k < l.nbr_of_philo)
		waitpid(-1, NULL, 0);
	unlinker((char *[]){"/forks", "/state", "/eat", "print", NULL});
	closer((void *[]){l.forks, l.state, l.eat, l.print, NULL});
}

int	thread_maker(t_init i)
{
	t_philo	*ph;
	t_lock	l;
	int		k;

	ph = NULL;
	unlinker((char *[]){"/forks", "/state", "/eat", "print", NULL});
	l.nbr_of_philo = i.nbr_of_philo;
	if (opener(&l))
		return (perror("sem_open failed"), 1);
	l.is_dead = 0;
	k = -1;
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&ph, k, i, &l))
			return (1);
	}
	execution(ph, l);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_init	i;

	if (argc == 5 || argc == 6)
	{
		check_format(argv);
		parsing(&i, argv);
		if (thread_maker(i))
			return (mem_manager(0, FREE_MEMORY), 1);
	}
	else
		return (error("wrong number of arguments\n"), 1);
	printf("-----------------------------\n\n");
	return (mem_manager(0, FREE_MEMORY), 0);
}
