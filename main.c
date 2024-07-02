/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/07/02 11:43:13 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				mails = 0;
pthread_mutex_t	mutex;

void	*routine(void)
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// read mails
		// increment
		// write mails
	}
	return (NULL);
}

void	parsing(t_philo **p, char *argv[])
{
	*p = mem_manager(sizeof(t_philo), 0, 'A');
	(*p)->nbr_of_philo = ft_atoi(argv[1]);
	(*p)->dying_time = ft_atoi(argv[2]);
	(*p)->eating_time = ft_atoi(argv[3]);
	(*p)->sleeping_time = ft_atoi(argv[4]);
	if (argv[5])
		(*p)->eating_right_time = ft_atoi(argv[5]);
}

void	thread_maker(t_philo *p)
{
	while (p->nbr_of_philo--)
		pthread_at
}

int	main(int argc, char *argv[])
{
	pthread_mutex_t	mutex;
	t_philo			*p;

	if (argc == 5 || argc == 6)
	{
		parsing(&p, argv);
		thread_maker(p);
	}
	else
		return (printf("wrong number of arguments\n"), 1);
	return (0);
}
