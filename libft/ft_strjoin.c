/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:04:24 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:06 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	size_t		len_str;
	char		*new_str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_str = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	new_str = malloc(len_str * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
	i++;
	}
	while (s2[j])
	{
		new_str[i] = s2[j];
	i++;
	j++;
	}
	new_str[i] = '\0';
	return (new_str);
}