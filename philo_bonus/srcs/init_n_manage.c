/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:11:38 by isb3              #+#    #+#             */
/*   Updated: 2024/09/27 09:29:08 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	opener(t_lock *l)
{
	(*l).forks = sem_open("/forks", O_CREAT, 0644, (*l).nbr_of_philo);
	(*l).state = sem_open("/state", O_CREAT, 0644, 1);
	(*l).eat = sem_open("/eat", O_CREAT, 0644, 1);
	(*l).print = sem_open("/print", O_CREAT, 0644, 1);
	if (!(*l).forks || !(*l).state || !(*l).eat || !(*l).print)
		return (1);
	return (0);
}

void	parsing(t_init *i, char *argv[])
{
	int	n_philo;

	n_philo = ft_atoi(argv[1]);
	if (n_philo > 200)
	{
		error(ft_strjoin("error: number of Philosophers",
				" is too high for this poor little computer\n"));
		mem_manager(0, FREE_MEMORY);
		exit(EXIT_FAILURE);
	}
	(*i).nbr_of_philo = n_philo;
	(*i).true_dying_time = (long)ft_atoi(argv[2]);
	(*i).eating_time = (long)ft_atoi(argv[3]) * 1000;
	(*i).sleeping_time = (long)ft_atoi(argv[4]) * 1000;
	if (argv[5])
		(*i).eating_counter = ft_atoi(argv[5]);
	else
		(*i).eating_counter = -1;
}

int	init_philo(t_philo **ph, int id, t_init i, t_lock *l)
{
	t_philo	*new_node;
	t_philo	*last_node;

	new_node = mem_manager(sizeof(t_philo), ALLOCATE);
	new_node->next = NULL;
	new_node->id = id;
	new_node->i = i;
	new_node->l = l;
	new_node->dying_time = get_time(&new_node->l->current_time)
		+ (new_node->i.true_dying_time);
	if (!*ph)
		*ph = new_node;
	else
	{
		last_node = *ph;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}
