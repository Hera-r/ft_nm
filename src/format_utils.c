#include "../include/ft_nm.h"

int	ft_nb_numb(unsigned int nb)
{
	int	n = 0;

	if (nb == 0)
		return 0;

	while (nb >= 16)
	{
		nb = nb / 16;
		n++;
	}
	return (n == 0) ? 1 : n;
}


void	ft_hexadecimal(unsigned int nb)
{
	char	*hexa;

	if (nb == 0)
	{
		write(1, "0", 1);
	}
	else
	{
		hexa = "0123456789abcdef";

		if (nb >= 16)
		{
			ft_hexadecimal(nb / 16);
			ft_hexadecimal(nb % 16);
		}
		else
			write(1, &hexa[nb], 1);
	}
}


void	ft_print_hexa(unsigned int nb) {
	int nb_num = ft_nb_numb(nb);
	
	for (int i = 0; i < (15 - nb_num); i++)
		ft_putchar_fd('0', STDOUT_FILENO);
	ft_hexadecimal(nb);
}


char *formated_ar_name(const char *ar_name)  // j'ai malloc dans cette fonction
{
    char raw_name[17];

    ft_memcpy(raw_name, ar_name, 16);
    raw_name[16] = '\0';

    for (int i = 15; i >= 0; i--) {
        if (raw_name[i] == ' ' || raw_name[i] == '/' || raw_name[i] == '\0') {
            raw_name[i] = '\0';
        } else
            break;
    }

    char *result = malloc(17);
    if (!result)
        return NULL;

    ft_strlcpy(result, raw_name, 17);

    return result;
}


void	ft_nm_error(const char *filename, const char *message)
{
	ft_putstr_fd("ft_nm: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
