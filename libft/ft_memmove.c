/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:05:05 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:29:44 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	const char	*new_src;
	char		*new_dest;

	new_src = src;
	new_dest = dest;
	if (new_src != new_dest)
	{
		if (new_src > new_dest)
		{
			while (count)
			{
				*(new_dest++) = *(new_src++);
			count--;
			}
		}
		else
		{
			while (count)
			{
				new_dest[count - 1] = new_src[count - 1];
				count--;
			}
		}
	}	
	return (dest);
}
