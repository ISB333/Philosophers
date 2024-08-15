/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:22 by adesille          #+#    #+#             */
/*   Updated: 2024/08/15 11:51:37 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define DEF "\033[0m"
# define YELLOW "\033[0;33m"
# define ORANGE "\033[38;2;255;165;0m" // RGB for orange

# define THINK 100
# define EAT 101
# define SLEEP 102
# define DIE 103
# define LEFT_FORK 104
# define RIGHT_FORK 105

typedef struct s_init
{
	int				nbr_of_philo;
	long			true_dying_time;
	int				eating_time;
	int				sleeping_time;
	int				eating_right_time;
}					t_init;

typedef struct s_memman
{
	void			*ptr;
	struct s_memman	*next;
}					t_memman;

typedef struct s_forks
{
	int				nbr_of_philo;
	pthread_mutex_t	*forks;
}					t_forks;

typedef struct s_lock
{
	int				is_dead;
	pthread_mutex_t	state_mutex;
	pthread_cond_t	cond;
}					t_lock;

typedef struct s_philo
{
	pthread_t		philo;
	long			dying_time;
	t_forks			f;
	t_init			i;
	t_lock			l;
	int				id;
	struct s_philo	*next;
}					t_philo;

/// SRCS ///

void				*philo_diner_table(void *num);
int					init_philo(t_philo **p, int id, void **hax);
void				parsing(t_init *i, char *argv[]);
int					joiner(t_philo *p);
void				*eating_time(t_philo *ph, struct timeval *current_time);
void				*sleeping_time(t_philo *ph, struct timeval *current_time);
int is_one_dead(t_philo *ph);
// int					is_philo_dead(int n, t_philo *ph);
void				*unlocker(void **m);
long				print_n_update(char *s, int n, struct timeval *current_time,
						int token);

/// UTILS ///

void				*mem_manager(size_t size, void *ptr, int token);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *str);
void				*ff(t_memman *mem_list);
char				*ft_strjoin(char const *s1, char const *s2);
int					error(char *msg);

#endif