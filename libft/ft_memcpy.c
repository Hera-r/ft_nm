/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:26:58 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:29:42 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (count)
	{
		*(char *)(dest + i) = *(char *)(src + i);
	i++;
	count--;
	}
	return (dest);
}
