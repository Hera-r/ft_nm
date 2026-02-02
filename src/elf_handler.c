#include "../include/ft_nm.h"


static int	fill_symbol_list(t_symbol *list, void *mem, Elf64_Shdr *symtab, Elf64_Shdr *sheader)
{
	Elf64_Sym	*symbo;
	Elf64_Shdr	*strtab;
	int			nb_symbols;
	int			i;
	int			j;

	symbo = (Elf64_Sym *)(mem + symtab->sh_offset);
	nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);
	strtab = &sheader[symtab->sh_link];
	i = -1;
	j = -1;
	while (++i < nb_symbols)
	{
		if (symbo[i].st_name == 0 || ELF64_ST_TYPE(symbo[i].st_info) == STT_FILE)
			continue ;
		j++;
		list[j].name = (char *)(mem + strtab->sh_offset + symbo[i].st_name);
		list[j].type = get_symbol_type(&symbo[i], sheader);
		list[j].is_undefined = (symbo[i].st_shndx == SHN_UNDEF);
		if (((Elf64_Ehdr *)mem)->e_type == ET_REL && symbo[i].st_shndx != SHN_UNDEF
			&& symbo[i].st_shndx < ((Elf64_Ehdr *)mem)->e_shnum)
			list[j].value = symbo[i].st_value - sheader[symbo[i].st_shndx].sh_addr;
		else
			list[j].value = symbo[i].st_value;
	}

	return (j + 1);
}

static int	count_valid_symbols(void *mem, Elf64_Shdr *symtab)
{
	Elf64_Sym	*symbo;
	int			nb_symbols;
	int			valid_count;
	int			i;

	symbo = (Elf64_Sym *)(mem + symtab->sh_offset);
	nb_symbols = symtab->sh_size / sizeof(Elf64_Sym);
	valid_count = 0;
	i = -1;
	while (++i < nb_symbols)
	{
		if (symbo[i].st_name == 0 || ELF64_ST_TYPE(symbo[i].st_info) == STT_FILE)
			continue ;
		valid_count++;
	}

	return (valid_count);
}


int	handle_elf_file(void *file_mem, char *filename)
{
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*sect_hdr;
	Elf64_Shdr	*symtab;
	t_symbol	*symbols_list;
	int			valid_count;

	ehdr = (Elf64_Ehdr *)file_mem;
	sect_hdr = (Elf64_Shdr *)(file_mem + ehdr->e_shoff);
	symtab = find_symtab(ehdr, sect_hdr);
	if (!symtab)
	{
		ft_nm_error(filename, "no symbols");
		return (0);
	}
	valid_count = count_valid_symbols(file_mem, symtab);
	symbols_list = malloc(sizeof(t_symbol) * valid_count);
	if (!symbols_list)
	{
		ft_nm_error(filename, "memory allocation failed");
		return (1);
	}
	fill_symbol_list(symbols_list, file_mem, symtab, sect_hdr);
	display_symbols(symbols_list, valid_count, ehdr);
	free(symbols_list);

	return (0);
}