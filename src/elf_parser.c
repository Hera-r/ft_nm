#include "../include/ft_nm.h"


char	get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr_tab)
{
	unsigned char	type;
	unsigned char	bind;
	Elf64_Shdr		*sect;
	Elf64_Xword		flags;

	type = ELF64_ST_TYPE(sym->st_info);
	bind = ELF64_ST_BIND(sym->st_info);

	if (sym->st_shndx == SHN_UNDEF)
	{
		if (bind == STB_WEAK)
			return ('w');
		return ('U');
	}

	if (sym->st_shndx == SHN_ABS)
		return ((bind == STB_LOCAL) ? 'a' : 'A');

	if (sym->st_shndx == SHN_COMMON)
		return ((bind == STB_LOCAL) ? 'c' : 'C');

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return ((sym->st_value != 0) ? 'V' : 'v');
		return ((sym->st_value != 0) ? 'W' : 'w');
	}

	sect = &shdr_tab[sym->st_shndx];
	flags = sect->sh_flags;

	if (flags & SHF_EXECINSTR)
		return ((bind == STB_LOCAL) ? 't' : 'T');

	if (sect->sh_type == SHT_NOBITS)
		return ((bind == STB_LOCAL) ? 'b' : 'B');

	if (flags & SHF_WRITE)
		return ((bind == STB_LOCAL) ? 'd' : 'D');

	if (flags & SHF_ALLOC)
		return ((bind == STB_LOCAL) ? 'r' : 'R');

	return ('?');
}

int	check_elf_magic(Elf64_Ehdr *ehdr)
{
	if (ehdr->e_ident[0] != ELFMAG0 || ehdr->e_ident[1] != ELFMAG1
		|| ehdr->e_ident[2] != ELFMAG2 || ehdr->e_ident[3] != ELFMAG3)
		return (1);
	return (0);
}

Elf64_Shdr	*find_symtab(Elf64_Ehdr *ehdr, Elf64_Shdr *section_header)
{
	Elf64_Shdr	*symtab;
	int			i;
	Elf64_Shdr	*current;

	symtab = NULL;
	i = -1;
	while (++i < ehdr->e_shnum)
	{
		current = (Elf64_Shdr *)((char *)section_header + (i * ehdr->e_shentsize));
		if (current->sh_type == SHT_SYMTAB)
		{
			symtab = current;
			break ;
		}
	}
	return (symtab);
}