/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:22 by adesille          #+#    #+#             */
/*   Updated: 2024/07/02 13:19:22 by adesille         ###   ########.fr       */
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

typedef struct s_memman
{
	void			*ptr;
	struct s_memman	*next;
}					t_memman;

typedef struct s_philo
{
	pthread_t		ph;
	struct s_philo	*next;
}					t_philo;

typedef struct s_init
{
	int				nbr_of_philo;
	int				dying_time;
	int				eating_time;
	int				sleeping_time;
	int				eating_right_time;
}					t_init;

void				*mem_manager(size_t size, void *ptr, int token);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *str);
void				*ff(t_memman *mem_list);
char				*ft_strjoin(char const *s1, char const *s2);

#endif