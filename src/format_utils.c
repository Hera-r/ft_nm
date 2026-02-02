#include "../include/ft_nm.h"

int	ft_nb_numb(unsigned long long nb)
{
	int	n;

	n = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 16;
		n++;
	}
	return (n);
}

void	ft_hexadecimal(unsigned long long nb)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_hexadecimal(nb / 16);
		ft_hexadecimal(nb % 16);
	}
	else
		ft_putchar_fd(hexa[nb], STDOUT_FILENO);
}

void	ft_print_hexa(unsigned long long nb)
{
	int				nb_num;
	int				i;
	unsigned long long	tmp;

	tmp = nb;
	nb_num = ft_nb_numb(tmp);
	i = -1;
	while (++i < (16 - nb_num))
		ft_putchar_fd('0', STDOUT_FILENO);
	ft_hexadecimal(nb);
}

char	*formated_ar_name(const char *ar_name)
{
	char	raw_name[17];
	char	*result;
	int		i;

	ft_memcpy(raw_name, ar_name, 16);
	raw_name[16] = '\0';
	i = 16;
	while (--i >= 0)
	{
		if (raw_name[i] == ' ' || raw_name[i] == '/' || raw_name[i] == '\0')
			raw_name[i] = '\0';
		else
			break ;
	}
	result = malloc(17);
	if (!result)
		return (NULL);
	ft_strlcpy(result, raw_name, 17);
	return (result);
}

void	ft_nm_error(const char *filename, const char *message)
{
	ft_putstr_fd("ft_nm: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}