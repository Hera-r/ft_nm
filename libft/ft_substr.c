/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:13:42 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:27 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	int		i;
	char	*copy;

	if (!s)
		return (NULL);
	i = 0;
	new_s = (char *)s + start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < (start + len))
		len = ft_strlen(s) - start;
	copy = malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (new_s[i] && len)
	{
		copy[i] = new_s[i];
	i++;
	len--;
	}
	copy[i] = '\0';
	return (copy);
}
