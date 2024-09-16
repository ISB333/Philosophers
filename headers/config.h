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

#ifndef CONFIG_H
# define CONFIG_H

# include "philo.h"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <sys/time.h>
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

#endif