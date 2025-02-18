/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:34:30 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:30:09 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_size(char *str, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] && i < size)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;

	i = 0;

	if (!dest && size == 0)
		return (0);
	len_d = ft_strlen_size(dest, size);
	while (len_d + i < (size - 1) && src[i] && size)
	{
		dest[len_d + i] = src[i];
	i++;
	}
	if (len_d < size)
		dest[len_d + i] = '\0';
	return (len_d + ft_strlen(src));
}

