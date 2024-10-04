/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:04 by adesille          #+#    #+#             */
/*   Updated: 2024/10/04 09:41:24 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	printer(t_philo *ph, char *s, int n, int token)
{
	long	precise_time;

	pthread_mutex_lock(&ph->l->m[PRINT_MUTEX]);
	if (is_he_dead(ph))
		return (pthread_mutex_unlock(&ph->l->m[PRINT_MUTEX]));
	precise_time = get_time() - ph->start_time;
	if (s)
	{
		if (token == EAT)
			printf(GREEN);
		if (token == SLEEP)
			printf(BLUE);
		if (token == DIE)
			printf(RED);
		if (token == LEFT_FORK)
			printf(YELLOW);
		if (token == RIGHT_FORK)
			printf(YELLOW);
		printf("%ld %d %s\n" DEF, precise_time, n, s);
	}
	pthread_mutex_unlock(&ph->l->m[PRINT_MUTEX]);
	return (1);
}

void	*philo_diner_table(void *num)
{
	t_philo	*ph;

	ph = (t_philo *)num;
	pthread_mutex_lock(&ph->l->m[EAT_MUTEX]);
	ph->dying_time = get_time() - ph->start_time + ph->i.true_dying_time;
	pthread_mutex_unlock(&ph->l->m[EAT_MUTEX]);
	while (!check_death(ph) && ph->i.eating_counter)
	{
		if (!thinking(ph))
			return (NULL);
		if (!eating(ph))
			return (NULL);
		if (!sleeping(ph))
			return (NULL);
	}
	return (NULL);
}

int	thread_maker(t_init i)
{
	t_philo	*ph;
	t_lock	l;
	int		k;

	ph = NULL;
	l.forks = mem_manager(i.nbr_of_philo * sizeof(pthread_mutex_t), ALLOCATE);
	l.nbr_of_philo = i.nbr_of_philo;
	l.is_dead = 0;
	if (mutex_init(&l, i.nbr_of_philo))
		return (1);
	k = -1;
	while (++k < i.nbr_of_philo)
	{
		if (init_philo(&ph, k, i, &l))
			return (1);
	}
	joiner(ph);
	mutex_destroyer(&l);
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
