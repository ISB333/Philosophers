/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:11:38 by isb3              #+#    #+#             */
/*   Updated: 2024/07/17 10:55:06 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(t_init *i, char *argv[])
{
	(*i).nbr_of_philo = ft_atoi(argv[1]);
	(*i).true_dying_time = (long)ft_atoi(argv[2]) * 1000 ;
	(*i).eating_time = ft_atoi(argv[3]);
	(*i).sleeping_time = ft_atoi(argv[4]);
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
	if (pthread_create(&new_node->philo, NULL, &philosopher, new_node))
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
