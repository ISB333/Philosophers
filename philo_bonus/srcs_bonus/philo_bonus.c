/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/10/03 14:16:28 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_diner_table(t_philo *ph)
{	
	sem_wait(ph->l->eat);
	ph->dying_time = get_time() - ph->start_time + ph->i.true_dying_time;
	sem_post(ph->l->eat);
	while (!check_death(ph) && ph->i.eating_counter)
	{
		if (!eating(ph))
			return (NULL);
		if (!thinking(ph))
			return (NULL);
		if (!sleeping(ph))
			return (NULL);
	}
	return (NULL);
}

void	execution(t_philo *ph, t_lock l)
{
	while (ph)
	{
		ph->start_time = get_time();
		ph->pid = fork();
		if (!ph->pid)
		{
			philo_diner_table(ph);
			mem_manager(0, FREE_MEMORY);
			unlinker((char *[]){"/forks", "/state", "/eat", "print", NULL});
			closer((void *[]){l.forks, l.state, l.eat, l.print, NULL});
			if (ph->i.eating_counter == -1 || !ph->i.eating_counter)
				kill(0, SIGKILL);
		}
		ph = ph->next;
	}
	int k = -1;
	while (++k < l.nbr_of_philo)
		waitpid(-1, NULL, 0);
	unlinker((char *[]){"/forks", "/state", "/eat", "print", NULL});
	closer((void *[]){l.forks, l.state, l.eat, l.print, NULL});
}

int	semaphore_maker(t_init i)
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
		if (semaphore_maker(i))
			return (mem_manager(0, FREE_MEMORY), 1);
	}
	else
		return (error("wrong number of arguments\n"), 1);
	printf("-----------------------------\n\n");
	return (mem_manager(0, FREE_MEMORY), 0);
}
