/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:03:53 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:25 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(char const *set, char s1, int count, int index)
{
	while (set[index])
	{
		if (s1 == set[index])
		{
			count++;
			return (count);
		}
	index++;
	}
	return (count);
}

static int	s_str(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	count;
	int	stock;

	i = 0;
	j = 0;
	count = 0;
	stock = 0;
	while (s1[i])
	{
		count = counter(set, s1[i], count, j);
		if (count == 0 || count == stock)
			return (i);
	stock = count;
	i++;
	j = 0;
	}
	return (i);
}

static int	e_str(char const *s1, char const *set)
{
	int	size;
	int	j;
	int	count;
	int	stock;

	j = 0;
	stock = 0;
	count = 0;
	size = ft_strlen(s1) - 1;
	while (s1[size])
	{
		count = counter(set, s1[size], count, j);
		if (count == 0 || count == stock)
			return (size);
	stock = count;
	size--;
	j = 0;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		size;
	char	*tmp;
	int		i;
	int		start;

	if (!s1)
		return (NULL);
	start = s_str(s1, set);
	tmp = (char *)s1 + start;
	size = (e_str(s1, set) - start) + 2;
	if (size < 0)
		size = 1;
	i = 0;
	new_str = malloc((size) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (start <= e_str(s1, set))
	{
		new_str[i] = tmp[i];
	i++;
	start++;
	}
	new_str[i] = '\0';
	return (new_str);
}
