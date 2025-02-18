/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:45:42 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:29:46 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t count)
{
	unsigned char	*new_ptr;

	new_ptr = ptr;
	while (count)
	{
		*new_ptr++ = (char)c;
	count--;
	}
	return (ptr);
}
