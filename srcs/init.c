/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:11:38 by isb3              #+#    #+#             */
/*   Updated: 2024/08/17 10:41:34 by adesille         ###   ########.fr       */
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

int	init_philo(t_philo **ph, int id, t_init i, t_lock l)
{
	t_philo	*new_node;
	t_philo	*last_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (mem_manager(0, 0, 'C'), 1);
	new_node->next = NULL;
	new_node->id = id;
	new_node->i = i;
	new_node->l = l;
	gettimeofday(&new_node->l.current_time, NULL);
	new_node->dying_time = (new_node->l.current_time.tv_sec * 1000) + (new_node->l.current_time.tv_usec
			/ 1000) + (new_node->i.true_dying_time);
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
