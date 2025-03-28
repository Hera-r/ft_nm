#include "../include/ft_nm.h"

char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr_tab)
{
	unsigned char type = ELF64_ST_TYPE(sym->st_info);
	unsigned char bind = ELF64_ST_BIND(sym->st_info);

	if (sym->st_shndx == SHN_UNDEF) {
		if (bind == STB_WEAK)
			return 'w'; 
		return 'U';
	}

	// 2) Symboles absolus (SHN_ABS) => 'A/a'
	if (sym->st_shndx == SHN_ABS)
		return (bind == STB_LOCAL) ? 'a' : 'A';

	// 3) Symboles "common" (SHN_COMMON) => 'C/c'
	if (sym->st_shndx == SHN_COMMON)
		return (bind == STB_LOCAL) ? 'c' : 'C';

	// 4) Weak symbol défini => 'W/w' ou 'V/v' (object)
	if (bind == STB_WEAK) {
		// STT_OBJECT => 'V'/'v'
		if (type == STT_OBJECT)
			return (sym->st_value != 0) ? 'V' : 'v';
		// Sinon 'W'/'w'
		return (sym->st_value != 0) ? 'W' : 'w';
	}

	// 5) On récupère la section pour déterminer la lettre (T, D, R, B, etc.)
	Elf64_Shdr *sect = &shdr_tab[sym->st_shndx];
	Elf64_Xword flags = sect->sh_flags;

	// Exécutable => 'T/t'
	if (flags & SHF_EXECINSTR)
		return (bind == STB_LOCAL) ? 't' : 'T';

	// .bss => SHT_NOBITS => 'B/b'
	if (sect->sh_type == SHT_NOBITS)
		return (bind == STB_LOCAL) ? 'b' : 'B';

	// Section writable => 'D/d' (souvent .data)
	if (flags & SHF_WRITE)
		return (bind == STB_LOCAL) ? 'd' : 'D';

	// Section allouée (SHF_ALLOC) non-writable => 'R/r' (souvent .rodata)
	if (flags & SHF_ALLOC)
		return (bind == STB_LOCAL) ? 'r' : 'R';

	// 6) Sinon => '?'
	return '?';
}



int	check_elf_magic(Elf64_Ehdr *ehdr) {
	if (ehdr->e_ident[0] != ELFMAG0 || ehdr->e_ident[1] != ELFMAG1 || ehdr->e_ident[2] != ELFMAG2 || ehdr->e_ident[3] != ELFMAG3) {
		return 1;
	}
	return 0;
}


Elf64_Shdr	*find_symtab(Elf64_Ehdr *ehdr, Elf64_Shdr *section_header)
{
	Elf64_Shdr *symtab = NULL;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		Elf64_Shdr *sy = (Elf64_Shdr *)((char *)section_header + (i * ehdr->e_shentsize));
		if (sy->sh_type == SHT_SYMTAB) {
			symtab = sy;
			break;
		}
	}

	return symtab;
}