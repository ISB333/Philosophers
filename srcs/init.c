/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:11:38 by isb3              #+#    #+#             */
/*   Updated: 2024/08/14 12:00:58 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(t_init *i, char *argv[])
{
	(*i).nbr_of_philo = ft_atoi(argv[1]);
	(*i).true_dying_time = (long)ft_atoi(argv[2]);
	(*i).eating_time = (long)ft_atoi(argv[3]) * 1000;
	(*i).sleeping_time = (long)ft_atoi(argv[4]) * 1000;
	if (argv[5])
		(*i).eating_right_time = ft_atoi(argv[5]);
}

int	init_philo(t_philo **p, int id, t_forks f, t_init i)
{
	t_philo	*new_node;
	t_philo	*last_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (mem_manager(0, 0, 'C'), 1);
	new_node->next = NULL;
	new_node->id = id;
	new_node->f = f;
	new_node->i = i;
	pthread_cond_init(&new_node->cond, NULL);
	if (pthread_create(&new_node->philo, NULL, &philo_diner_table, new_node))
		return (1);
	if (!*p)
		*p = new_node;
	else
	{
		last_node = *p;
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
