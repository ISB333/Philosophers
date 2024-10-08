/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:22 by adesille          #+#    #+#             */
/*   Updated: 2024/10/03 13:40:14 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define DEF "\033[0m"
# define YELLOW "\033[0;33m"
# define ORANGE "\033[38;2;255;165;0m"

# define THINK 100
# define EAT 101
# define SLEEP 102
# define DIE 103
# define LEFT_FORK 104
# define RIGHT_FORK 105

# define STATE_MUTEX 0
# define EAT_MUTEX 1
# define PRINT_MUTEX 2

# define ALLOCATE 300
# define FREE_MEMORY 301

typedef struct s_memman
{
	void			*ptr;
	struct s_memman	*next;
}					t_memman;

typedef struct s_init
{
	int				nbr_of_philo;
	long			true_dying_time;
	long			eating_time;
	long			sleeping_time;
	int				eating_counter;
}					t_init;

typedef struct s_lock
{
	int				is_dead;
	int				nbr_of_philo;
	sem_t			*state;
	sem_t			*eat;
	sem_t			*print;
	sem_t			*forks;
	struct timeval	current_time;
}					t_lock;

typedef struct s_philo
{
	pid_t			pid;
	long			dying_time;
	long			start_time;
	t_init			i;
	t_lock			*l;
	int				id;
	struct s_philo	*next;
}					t_philo;

/// SRCS ///
void				*philo_diner_table(t_philo *ph);
int					init_philo(t_philo **ph, int id, t_init i, t_lock *l);
void				parsing(t_init *i, char *argv[]);
int					eating(t_philo *ph);
int					sleeping(t_philo *ph);
int					thinking(t_philo *ph);
int					is_he_dead(t_philo *ph);
int					opener(t_lock *l);
void				closer(void *name[]);
void				unlinker(char *name[]);
int					printer(t_philo *ph, char *s, int n, int token);
long				get_time(void);
int					is_num(char c);
void				check_format(char *argv[]);
int					is_he_dead(t_philo *ph);
int					check_death(t_philo *ph);
void				ft_usleep(long long time);
void				killer(t_philo *ph);

void				*mem_manager(size_t size, int token);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *str);
void				*ff(t_memman *mem_list);
char				*ft_strjoin(char const *s1, char const *s2);
int					error(char *msg);

#endif