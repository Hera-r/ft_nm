/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:12:29 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:20 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && len)
	{
		while (j < ft_strlen(to_find) && len >= ft_strlen(to_find))
		{
			if (str[i + j] == to_find[j] && j != ft_strlen(to_find) - 1)
			{
			j++;
			}
			else if ((j == ft_strlen(to_find) - 1) && str[i + j] == to_find[j])
			{
				return (i);
			}
			else
				j = ft_strlen(to_find);
		}
	i++;
	len--;
	j = 0;
	}
	return (-1);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	o;

	if (!str && len == 0)
		return (0);
	o = -1;
	if (*to_find == 0)
		return ((char *)str);
	i = ft_findstr(str, to_find, len);
	if (i == o)
		return (0);
	return ((char *)str + i);
}
