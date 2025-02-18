/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:22:24 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 22:29:16 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
	{
		n *= -1;
		return (n);
	}
	return (n);
}

static int	count_str(int n)
{
	int	count;
	int	n_abs;

	count = 0;
	n_abs = ft_abs(n);
	if (n == -2147483648)
		return (count + 11);
	if (n < 0)
	{
		count++;
	}
	while (n_abs > 0)
	{
		n_abs = n_abs / 10;
	count++;
	}
	return (count);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str_num;
	int		new_n;

	size = count_str(n);
	if (n == 0)
		size = 1;
	new_n = ft_abs(n);
	str_num = malloc((size + 1) * sizeof(char));
	if (n == -2147483648)
		return (ft_strcpy(str_num, "-2147483648"));
	if (n == 0)
		return (ft_strcpy(str_num, "0"));
	if (str_num == NULL)
		return (NULL);
	if (n < 0)
		str_num[0] = '-';
	str_num[size] = '\0';
	while (new_n > 0)
	{
		str_num[size - 1] = (new_n % 10) + '0';
		new_n = new_n / 10;
		size--;
	}
	return (str_num);
}
