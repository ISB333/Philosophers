/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:09:02 by adesille          #+#    #+#             */
/*   Updated: 2024/09/27 10:08:15 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *msg)
{
	msg = ft_strjoin(ft_strjoin(RED, msg), DEF);
	return (write(2, msg, ft_strlen(msg)));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = mem_manager(len * sizeof(char), ALLOCATE);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, (ft_strlen(s1) + 1));
	ft_strlcpy(&str[ft_strlen(s1)], s2, (ft_strlen(s2) + 1));
	return (str);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nbr;

	sign = 1;
	i = 0;
	nbr = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = (nbr * 10) + ((nptr[i++]) - 48);
	return (nbr * sign);
}
