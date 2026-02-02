#ifndef FT_NM_H
#define FT_NM_H

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ar.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <elf.h>
#include <sys/stat.h>
#include "../libft/libft.h"


typedef struct s_symbol
{
	char		*name;
	char		type;
	uint64_t	value;
	int			is_undefined;
}	t_symbol;


int				check_elf_magic(Elf64_Ehdr *ehdr);
int				handle_elf_file(void *file_mem, char *filename);
char			get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr_tab);
Elf64_Shdr		*find_symtab(Elf64_Ehdr *ehdr, Elf64_Shdr *section_header);
void			display_symbols(t_symbol *symbols_list, int count, Elf64_Ehdr *ehdr);


int					ft_nb_numb(unsigned long long nb);
void				ft_hexadecimal(unsigned long long nb);
void				ft_print_hexa(unsigned long long nb);
char				*formated_ar_name(const char *ar_name);
void				ft_nm_error(const char *filename, const char *message);


int				handle_archive(void *ptr, char *end, const char *filename);

#endif
