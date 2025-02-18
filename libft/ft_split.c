/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:19:15 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:29:55 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	element_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
			i++;
		}
	}
	return (count);
}

static char	*strdup_index(char const *s, int st, int end)
{
	char	*newstr;
	int		size;
	int		i;

	size = (end - st) + 1;
	i = 0;
	newstr = malloc(size * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (st < end)
	{
		newstr[i] = s[st];
		i++;
		st++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
	i++;
	}
	free(tab);
	return (0);
}

static char	**append_list(char const *s, char c, char **tab)
{
	int	i;
	int	index;
	int	start;

	i = 0;
	start = 0;
	index = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
			i++;
			tab[index] = strdup_index(s, start, i);
			if (!tab[index])
				return (free_tab(tab));
			index++;
		}
	}
	tab[index] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		size;

	if (!s)
		return (NULL);
	size = element_count(s, c);
	tab = malloc((size + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	append_list(s, c, tab);
	return (tab);
}

