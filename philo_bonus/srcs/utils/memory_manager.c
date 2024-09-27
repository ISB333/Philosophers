/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:28:31 by isb3              #+#    #+#             */
/*   Updated: 2024/09/27 09:18:49 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_node(t_memman *new_node, t_memman **mem_list, void *ptr)
{
	t_memman	*last_node;

	new_node->ptr = ptr;
	new_node->next = NULL;
	if (!*mem_list)
		*mem_list = new_node;
	else
	{
		last_node = *mem_list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	*allocate(t_memman **mem_list, size_t size)
{
	t_memman	*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		mem_manager(0, FREE_MEMORY);
		exit(EXIT_FAILURE);
	}
	new_node = malloc(sizeof(t_memman));
	if (!new_node)
	{
		free(ptr);
		mem_manager(0, FREE_MEMORY);
		exit(EXIT_FAILURE);
	}
	init_node(new_node, mem_list, ptr);
	return (ptr);
}

void	*free_ptr(t_memman **mem_list, void *ptr)
{
	t_memman	*mem_temp;
	t_memman	*prev;

	mem_temp = *mem_list;
	prev = NULL;
	while (mem_temp)
	{
		if (mem_temp->ptr == ptr)
		{
			free(mem_temp->ptr);
			if (prev)
				prev->next = mem_temp->next;
			else
				*mem_list = mem_temp->next;
			free(mem_temp);
			break ;
		}
		prev = mem_temp;
		mem_temp = mem_temp->next;
	}
	return (NULL);
}

void	*mem_manager(size_t size, int token)
{
	static t_memman	*mem_list = NULL;

	if (token == ALLOCATE)
		return (allocate(&mem_list, size));
	if (token == FREE_MEMORY)
	{
		ff(mem_list);
		mem_list = NULL;
		return (NULL);
	}
	return (NULL);
}
