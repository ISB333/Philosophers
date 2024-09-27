/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:11:38 by isb3              #+#    #+#             */
/*   Updated: 2024/09/27 09:28:52 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroyer(t_lock *l)
{
	int	k;

	k = -1;
	while (++k < 3)
		pthread_mutex_destroy(&(*l).m[k]);
}

int	mutex_init(t_lock *l, int nbr_of_philo)
{
	int	k;

	k = -1;
	while (++k < nbr_of_philo)
		if (pthread_mutex_init(&(*l).forks[k], NULL))
			return (error("error while initializing mutex\n"), 1);
	k = -1;
	while (++k < 3)
		if (pthread_mutex_init(&(*l).m[k], NULL))
			return (error("error while initializing mutex\n"), 1);
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
	if (pthread_create(&new_node->philo, NULL, &philo_diner_table, new_node))
		return (1);
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

int	joiner(t_philo *p)
{
	while (p)
	{
		if (pthread_join(p->philo, NULL) != 0)
			return (1);
		p = p->next;
	}
	return (0);
}
