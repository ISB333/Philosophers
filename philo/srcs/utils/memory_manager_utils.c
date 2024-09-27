/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:57:38 by adesille          #+#    #+#             */
/*   Updated: 2024/09/27 09:19:02 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*error_init(char *msg, char *file)
{
	char	*s;

	s = ft_strjoin(ft_strjoin("minihell: ", file), ": ");
	return (ft_strjoin(s, msg));
}

void	*ff(t_memman *mem_list)
{
	t_memman	*temp;

	while (mem_list)
	{
		temp = mem_list;
		mem_list = mem_list->next;
		if (temp->ptr)
		{
			free(temp->ptr);
			temp->ptr = NULL;
		}
		free(temp);
	}
	return (NULL);
}
