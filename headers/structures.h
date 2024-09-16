/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:22 by adesille          #+#    #+#             */
/*   Updated: 2024/09/09 12:44:30 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "philo.h"

typedef struct s_memman
{
	void			*ptr;
	struct s_memman	*next;
}					t_memman;

typedef struct s_init
{
	int				nbr_of_philo;
	long			true_dying_time;
	int				eating_time;
	int				sleeping_time;
	int				eating_counter;
}					t_init;

typedef struct s_lock
{
	int				is_dead;
	int				nbr_of_philo;
	pthread_mutex_t	m[3];
	pthread_mutex_t	*forks;
	struct timeval	current_time;
}					t_lock;

typedef struct s_philo
{
	pthread_t		philo;
	long			dying_time;
	t_init			i;
	t_lock			*l;
	int				id;
	struct s_philo	*next;
}					t_philo;

#endif