/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:31:58 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:02 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_space;
	size_t	len_str;
	int		i;

	len_str = ft_strlen(s) + 1;
	new_space = malloc(len_str * sizeof(char));
	i = 0;
	if (new_space == NULL)
		return (NULL);
	while (s[i])
	{
		new_space[i] = s[i];
	i++;
	}
	new_space[i] = '\0';
	return (new_space);
}

