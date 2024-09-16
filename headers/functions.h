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

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "philo.h"

/// SRCS ///
void				*philo_diner_table(void *num);
int					init_philo(t_philo **ph, int id, t_init i, t_lock *l);
int					mutex_init(t_lock *l, int nbr_of_philo);
void				mutex_destroyer(t_lock *l);
void				parsing(t_init *i, char *argv[]);
int					joiner(t_philo *p);
void				*eating(t_philo *ph, struct timeval *current_time);
void				*sleeping(t_philo *ph);
void				*thinking(t_philo *ph);
int					is_he_dead(t_philo *ph);
void				*unlocker(void **m);
void				*printer(t_philo *ph, char *s, int n, int token);
long				get_time(struct timeval *current_time);
int					is_num(char c);
void				check_format(char *argv[]);
int					is_he_dead(t_philo *ph);
int					check_death(t_philo *ph);

#endif