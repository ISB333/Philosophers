/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:48:22 by adesille          #+#    #+#             */
/*   Updated: 2024/09/09 12:44:30 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_MANAGER_H
# define MEM_MANAGER_H

# include "philo.h"

void				*mem_manager(size_t size, int token);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *str);
void				*ff(t_memman *mem_list);
char				*ft_strjoin(char const *s1, char const *s2);
int					error(char *msg);

#endif