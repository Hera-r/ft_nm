/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:15:41 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:16 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		size;
	char	*newstr;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s) + 1;
	i = 0;
	newstr = malloc(size * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (s[i])
	{
		newstr[i] = f(i, s[i]);
	i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
