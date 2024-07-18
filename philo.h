/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:22 by adesille          #+#    #+#             */
/*   Updated: 2024/07/18 08:46:39 by isb3             ###   ########.fr       */
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
	pthread_mutex_t	state_mutex;
	pthread_cond_t	state_cond;
}					t_forks;

typedef struct s_philo
{
	pthread_t		philo;
	long			dying_time;
	t_forks			f;
	t_init			i;
	int				id;
	struct s_philo	*next;
}					t_philo;

/// SRCS ///

void				*philo_diner_table(void *num);
int					init_philo(t_philo **p, int id, t_forks f, t_init i);
void				parsing(t_init *i, char *argv[]);
int					joiner(t_philo *p);

/// UTILS ///

void				*mem_manager(size_t size, void *ptr, int token);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *str);
void				*ff(t_memman *mem_list);
char				*ft_strjoin(char const *s1, char const *s2);
int					error(char *msg);

#endif