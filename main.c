/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/07/13 07:18:40 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	? To return a value, we should malloc an int * to store the value we want to return, then cast it to (void *)
	e.g :
		if (pthread_join(th, (void**) &res) != 0)
		*in the routine*:
		*result = value;
		return (void*) result;

	* 1- Philosophers eat with right & left forks
	* 2- Finished eating, put his forks back on the table
	* 3- Sleep
	* 4- Wake-up & Think

	! Conditions :
		! - fork = nbr_of_philo / 2 (1 if 1 nbr_of_philo)
		! - Each philosopher has a fork on their left and their right
		! - Each philosopher has a number from 1 to nbr_of_philo
			! -> Philo 1 sits next to nbr_of_philo
		! - To prevent philosophers from duplicating forks, 
			! you should protect the forks state with a mutex for each of them
		! - They should never die starving
		! - They don't speak to each other
		! - They don't know if another is about to die
*/

int				mails = 0;

void	*routine(void *arg)
{
	pthread_mutex_t *mutex;

	mutex = arg;
	for (int i = 0; i < 100; i++)
	{
		pthread_mutex_lock(mutex);
		mails++;
		pthread_mutex_unlock(mutex);
		// read mails
		// increment
		// write mails
	}
	return (NULL);
}

void	parsing(t_init **i, char *argv[])
{
	*i = mem_manager(sizeof(t_init), 0, 'A');
	(*i)->nbr_of_philo = ft_atoi(argv[1]);
	(*i)->dying_time = ft_atoi(argv[2]);
	(*i)->eating_time = ft_atoi(argv[3]);
	(*i)->sleeping_time = ft_atoi(argv[4]);
	if (argv[5])
		(*i)->eating_right_time = ft_atoi(argv[5]);
}

int	init_philo(t_philo **p, pthread_mutex_t *mutex)
{
	t_philo	*new_node;
	t_philo	*last_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (mem_manager(0, 0, 'C'), 1);
	new_node->next = NULL;
	if (pthread_create(&new_node->ph, NULL, &routine, mutex))
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
		if (pthread_join(p->ph, NULL) != 0)
			return (1);
		p = p->next;
	}
	return (0);
}

int	thread_maker(t_init *i, pthread_mutex_t *mutex)
{
	t_philo	*p;

	p = NULL;
	while (i->nbr_of_philo--)
		if (init_philo(&p, mutex))
			return (1);
	joiner(p);
	pthread_mutex_destroy(mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_init	*i;

	static pthread_mutex_t	mutex;
	if (argc == 5 || argc == 6)
	{
		parsing(&i, argv);
		thread_maker(i, &mutex);
	}
	else
		return (error("wrong number of arguments\n"), 1);
	return (0);
}
