#include "philo.h"


int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_format(char *argv[])
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (argv[++i])
	{
		k = -1;
		while (argv[i][++k])
			if (!is_num(argv[i][k]))
				return (error("wrong format\n"), exit(EXIT_FAILURE));
	}
}

int	is_he_dead(t_philo *ph)
{
	int	status;

	pthread_mutex_lock(&ph->l->state_mutex);
	status = ph->l->is_dead;
	pthread_mutex_unlock(&ph->l->state_mutex);
	return (status);
}

int check_death(t_philo *ph)
{
	long	precise_time;

	pthread_mutex_lock(&ph->l->state_mutex);
	precise_time = update_time(&ph->l->current_time);
	if (precise_time >= ph->dying_time && !ph->l->is_dead)
	{
		ph->l->is_dead = 1;
		printf(RED "%ld %d died\n" DEF, precise_time, ph->id);
		pthread_mutex_unlock(&ph->l->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->l->state_mutex);
	return (0);
}
