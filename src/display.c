#include "../include/ft_nm.h"



static int	symbol_cmp(const void *a, const void *b)
{
	t_symbol	*s1;
	t_symbol	*s2;

	s1 = (t_symbol *)a;
	s2 = (t_symbol *)b;
	return (ft_strcmp(s1->name, s2->name));
}


void	display_symbols(t_symbol *symbols_list, int count, Elf64_Ehdr *ehdr)
{
	int	i;

	qsort(symbols_list, count, sizeof(t_symbol), symbol_cmp);
	i = -1;
	while (++i < count)
	{
		if (symbols_list[i].is_undefined)
		{
			ft_putstr_fd("                 ", STDOUT_FILENO);
			ft_putchar_fd(symbols_list[i].type, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(symbols_list[i].name, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else if (symbols_list[i].value == 0 && ehdr->e_type == ET_REL)
		{
			ft_putstr_fd("0000000000000000", STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putchar_fd(symbols_list[i].type, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(symbols_list[i].name, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else if (symbols_list[i].value == 0)
		{
			ft_putstr_fd("                 ", STDOUT_FILENO);
			ft_putchar_fd(symbols_list[i].type, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(symbols_list[i].name, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else
		{
			ft_print_hexa(symbols_list[i].value);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putchar_fd(symbols_list[i].type, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			ft_putstr_fd(symbols_list[i].name, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
}