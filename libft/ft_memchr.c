/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:50:49 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:29:37 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buffer, int c, size_t count)
{
	char	*new_b;
	int		i;

	i = 0;
	new_b = (char *)buffer;
	while (count)
	{
		if (new_b[i] == (char)c)
			return (new_b + i);
	i++;
	count--;
	}
	return (0);
}
